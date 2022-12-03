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
    explicit IWorker(Request request, ITableStorage* storage): request(std::move(request)), storage(storage){}
    virtual Request operate() = 0;

    Request request;
    ITableStorage* storage;
};

class InsertWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override {

    }
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

    }
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    Request operate() override{

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
    }

    IWorker* get(Request& request, ITableStorage* storage){
        return factory.get(request.type)(request, storage);
    }

private:
    GenericObjectFactory<requestType, IWorker, Request, ITableStorage*> factory;
};

#endif // IWORKER_H
