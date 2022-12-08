// Copyright 2022 Ogrebatel

#ifndef IWORKER_H
#define IWORKER_H

#include <iostream>
#include <functional>
#include <utility>
#include "boost/asio.hpp"
#include "InternalEntities.h"
#include "IHashTable.h"
#include "ITableStorage.h"

class IWorker {
public:
    explicit IWorker(Request request, ITableStorage* storage):
            _request(std::move(request)), _storage(storage){}
    virtual Request operate() = 0;
    virtual ~IWorker() = default;

    Request _request;
    ITableStorage* _storage;
};

class InsertWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override {
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(table->Insert(_request._key, _request._value)){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }
        return answer;
    }
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(table->Remove(_request._key)){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }
        return answer;
    }
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(table->Find(_request._key)){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }
        return answer;
    }
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(table->Clear()){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }
        return answer;
    }
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        size_t size = table->GetSize();

        const auto* begin = reinterpret_cast<const uint8_t*>(&size);
        const auto* end = begin + sizeof(size);
        answer._value = std::vector<uint8_t>(begin, end);

        answer._status = Status::OK;
        return answer;
    }
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        answer._value = table->Get(_request._key);

        if(!answer._value.empty()){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }

        answer._key = _request._key;
        return answer;
    }
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(table->Update(_request._key, _request._value)){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }
        return answer;
    }
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(table){
            answer._status = Status::FAILURE;
            return answer;
        }

        if(_storage->CreateTable(_request._table_name)){
            answer._status = Status::OK;
        } else {
            answer._status = Status::FAILURE;
        }

        return answer;
    }
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        auto table = _storage->GetTable(_request._table_name);
        if(!table){
            answer._status = Status::FAILURE;
            return answer;
        }

        answer._status = Status::OK;
        return answer;
    }
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        if(!_storage->DeleteTable(_request._table_name)){
            answer._status = Status::FAILURE;
            return answer;
        }

        answer._status = Status::OK;
        return answer;
    }
};

class GetNumTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer._table_name = _request._table_name;
        answer._type = _request._type;

        size_t size = _storage->GetNumTables();

        const auto* begin = reinterpret_cast<const uint8_t*>(&size);
        const auto* end = begin + sizeof(size);
        answer._value = std::vector<uint8_t>(begin, end);

        answer._status = Status::OK;
        return answer;
    }
};

class ShowTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
//        _storage->ShowTables();
        return _request; //will be implemented as a feature
    }
};




template<class ID,class Base, class ... Args> class GenericObjectFactory{
private:
    typedef Base* (*fInstantiator)(Args ...);
    template<class Derived> static Base* instantiator(Args ... args){
        return new Derived(args ...);
    }
    std::map<ID,fInstantiator> classes;

public:
    GenericObjectFactory()= default;
    template<class Derived> void add(ID id){
        classes[id]=&instantiator<Derived>;
    }
    fInstantiator get(ID id){
        return classes[id];
    }

};

class workerFactory{
public:
    workerFactory(){
        factory.add<InsertWorker>(requestType::INSERT);
        factory.add<RemoveWorker>(requestType::REMOVE);
        factory.add<FindWorker>(requestType::FIND);
        factory.add<ClearWorker>(requestType::CLEAR);
        factory.add<GetSizeWorker>(requestType::GET_SIZE);
        factory.add<GetWorker>(requestType::GET);
        factory.add<UpdateWorker>(requestType::UPDATE);

        factory.add<GetTableWorker>(requestType::GET_TABLE);
        factory.add<CreateTableWorker>(requestType::CREATE_TABLE);
        factory.add<DeleteTableWorker>(requestType::DELETE_TABLE);
        factory.add<GetNumTablesWorker>(requestType::GET_NUM_TABLES);
        factory.add<ShowTablesWorker>(requestType::SHOW_TABLES);
    }

    IWorker* get(Request& request, ITableStorage* storage){
        return factory.get(request._type)(request, storage);
    }

private:
    GenericObjectFactory<requestType, IWorker, Request, ITableStorage*> factory;
};

#endif // IWORKER_H
