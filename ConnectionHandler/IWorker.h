//
// Created by ogrebatel on 03.12.22.
//

#ifndef IWORKER_H
#define IWORKER_H

#include "genericObjectFactory.h"
#include "IHashTable.h"
#include "InternalEntities.h"
#include "ITableStorage.h"

#include <boost/asio.hpp>
#include <iostream>
#include <functional>
#include <utility>

class IWorker {
public:
    explicit IWorker(std::shared_ptr<Request> request, ITableStorage* storage):
            _request(std::move(request)), _storage(storage){}
    virtual Request operate() = 0;
    virtual ~IWorker() = default;

    std::shared_ptr<Request> _request;
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
        factory.add<InsertWorker>(RequestType::INSERT);
        factory.add<RemoveWorker>(RequestType::REMOVE);
        factory.add<FindWorker>(RequestType::FIND);
        factory.add<ClearWorker>(RequestType::CLEAR);
        factory.add<GetSizeWorker>(RequestType::GET_SIZE);
        factory.add<GetWorker>(RequestType::GET);
        factory.add<UpdateWorker>(RequestType::UPDATE);

        factory.add<GetTableWorker>(RequestType::GET_TABLE);
        factory.add<CreateTableWorker>(RequestType::CREATE_TABLE);
        factory.add<DeleteTableWorker>(RequestType::DELETE_TABLE);
        factory.add<GetNumTablesWorker>(RequestType::GET_NUM_TABLES);
        factory.add<ShowTablesWorker>(RequestType::SHOW_TABLES);
    }

    IWorker* get(std::shared_ptr<Request> request, ITableStorage* storage){
        return factory.get(request->_type)(request, storage);
    }

private:
    GenericObjectFactory<RequestType, IWorker, std::shared_ptr<Request>, ITableStorage*> factory;
};

Request InsertWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    if(table->Insert(_request->_key, _request->_value)){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }
    return answer;
}

Request RemoveWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    if(table->Remove(_request->_key)){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }
    return answer;
}

Request FindWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    if(table->Find(_request->_key)){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }
    return answer;
}

Request ClearWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
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

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
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

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    answer._value = table->Get(_request->_key);

    if(!answer._value.empty()){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }

    answer._key = _request->_key;
    return answer;
}

Request UpdateWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    if(table->Update(_request->_key, _request->_value)){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }
    return answer;
}

Request CreateTableWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(table){
        answer._status = Status::FAILURE;
        return answer;
    }

    if(_storage->CreateTable(_request->_table_name)){
        answer._status = Status::OK;
    } else {
        answer._status = Status::FAILURE;
    }

    return answer;
}

Request GetTableWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    auto table = _storage->GetTable(_request->_table_name);
    if(!table){
        answer._status = Status::FAILURE;
        return answer;
    }

    answer._status = Status::OK;
    return answer;
}

Request DeleteTableWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    if(!_storage->DeleteTable(_request->_table_name)){
        answer._status = Status::FAILURE;
        return answer;
    }

    answer._status = Status::OK;
    return answer;
}

Request GetNumTablesWorker::operate() {
    Request answer;

    answer._table_name = _request->_table_name;
    answer._type = _request->_type;

    size_t size = _storage->GetNumTables();

    const auto* begin = reinterpret_cast<const uint8_t*>(&size);
    const auto* end = begin + sizeof(size);
    answer._value = std::vector<uint8_t>(begin, end);

    answer._status = Status::OK;
    return answer;
}

Request ShowTablesWorker::operate() {
//        _storage->ShowTables();
    return {}; //will be implemented as a feature
}

#endif // IWORKER_H
