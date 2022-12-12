//
// Created by ogrebatel on 03.12.22.
//

#ifndef IWORKER_H
#define IWORKER_H

#include <iostream>
#include <functional>
#include <utility>
#include "boost/asio.hpp"
#include "InternalEntities.h"
#include "IHashTable.h"
#include "ITableStorage.h"
#include "genericObjectFactory.h"

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
    Request operate() override;
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class GetNumTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
};

class ShowTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override;
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

Request InsertWorker::operate() {
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

Request RemoveWorker::operate() {
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

Request FindWorker::operate() {
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

Request ClearWorker::operate() {
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

Request GetSizeWorker::operate() {
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

Request GetWorker::operate() {
    Request answer;

    answer._table_name = _request._table_name;
    answer._type = _request._type;

    for (int i = 1; i < 50000; ++i) {
        std::string s;
        s.append(std::to_string(i));
    }

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

Request UpdateWorker::operate() {
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

Request CreateTableWorker::operate() {
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

Request GetTableWorker::operate() {
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

Request DeleteTableWorker::operate() {
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

Request GetNumTablesWorker::operate() {
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

Request ShowTablesWorker::operate() {
//        _storage->ShowTables();
    return _request; //will be implemented as a feature
}

#endif // IWORKER_H
