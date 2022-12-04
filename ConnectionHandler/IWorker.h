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
    explicit IWorker(Request request, ITableStorage* storage, IHashTable* table):
    request(std::move(request)), storage(storage), table(table){}
    virtual Request operate() = 0;
    virtual ~IWorker() = default;

    Request request;
    ITableStorage* storage;
    IHashTable* table;
};

class InsertWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override {
        table->Insert(request.key, request.value);
        return request;
    }
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->Remove(request.key);
        return request;
    }
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->Find(request.key);
        return request;
    }
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->Clear();
        return request;
    }
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->GetSize();
        return request;
    }
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->Get(request.key);
        return request;
    }
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        table->Update(request.key, request.value);
        return request;
    }
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->CreateTable(request.key);
        return request;
    }
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->GetTable(request.key);
        return request;
    }
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->DeleteTable(request.key);
        return request;
    }
};

class GetNumTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->GetNumTables();
        return request;
    }
};

class ShowTablesWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{
        storage->ShowTables();
        return request;
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

    IWorker* get(Request& request, ITableStorage* storage, IHashTable* table){
        return factory.get(request.type)(request, storage, table);
    }

private:
    GenericObjectFactory<requestType, IWorker, Request, ITableStorage*, IHashTable*> factory;
};

#endif // IWORKER_H
