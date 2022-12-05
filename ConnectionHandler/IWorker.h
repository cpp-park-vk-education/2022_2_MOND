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
    request(std::move(request)), storage(storage){}
    virtual Request operate() = 0;
    virtual ~IWorker() = default;

    Request request;
    ITableStorage* storage;
};

class InsertWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override {
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(table->Insert(request.key, request.value)){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }
        return answer;
    }
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(table->Remove(request.key)){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }
        return answer;
    }
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(table->Find(request.key)){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }
        return answer;
    }
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(table->Clear()){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }
        return answer;
    }
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        size_t size = table->GetSize();

        const auto* begin = reinterpret_cast<const uint8_t*>(&size);
        const auto* end = begin + sizeof(size);
        answer.value = std::vector<uint8_t>(begin, end);

        answer.status = Status::OK;
        return answer;
    }
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        answer.value = table->Get(request.key);

        if(!answer.value.empty()){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }

        answer.key = request.key;
        return answer;
    }
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(table->Update(request.key, request.value)){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }
        return answer;
    }
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        if(storage->CreateTable(request.key)){
            answer.status = Status::OK;
        } else {
            answer.status = Status::FAILURE;
        }

        return answer;
    }
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        auto table = storage->GetTable(request.table_name);
        if(!table){
            answer.status = Status::FAILURE;
            return answer;
        }

        answer.status = Status::OK;
        return answer;
    }
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        if(!storage->DeleteTable(request.table_name)){
            answer.status = Status::FAILURE;
            return answer;
        }

        answer.status = Status::OK;
        return answer;
    }
};

class GetNumTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        Request answer;

        answer.table_name = request.table_name;
        answer.type = request.type;

        size_t size = storage->GetNumTables();

        const auto* begin = reinterpret_cast<const uint8_t*>(&size);
        const auto* end = begin + sizeof(size);
        answer.value = std::vector<uint8_t>(begin, end);

        answer.status = Status::OK;
        return answer;
    }
};

class ShowTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->ShowTables();
        return request; //will be implemented as a feature
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
        return factory.get(request.type)(request, storage);
    }

private:
    GenericObjectFactory<requestType, IWorker, Request, ITableStorage*> factory;
};

#endif // IWORKER_H
