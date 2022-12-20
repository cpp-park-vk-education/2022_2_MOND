//
// Created by ogrebatel on 21.11.22.
//

#ifndef MOND_DB_CONNECTIONWORKER_H
#define MOND_DB_CONNECTIONWORKER_H

#include <utility>

#include "InternalEntities.h"
#include "BoostIFace.hpp"


class ITableStorage{

};

class IHashTable{

};

class IController{

};

class IDBSaverToDisk{

};

class ISerializer{

};

class IWorker {
public:
    IWorker(IHashTable* _hashTable, ITableStorage* _tableStorage): hashTable(_hashTable), tableStorage(_tableStorage){}
    virtual bool operateWithClient(std::shared_ptr<Connection> conn) = 0;

    IHashTable* hashTable;
    ITableStorage* tableStorage;
};

class InsertWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class RemoveWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class FindWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class ClearWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class GetSizeWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class GetWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class UpdateWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class CreateTableWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class GetTableWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
    }
};

class DeleteTableWorker : public IWorker{
    using IWorker::IWorker;
    bool operateWithClient(std::shared_ptr<Connection> conn) override{
        return true;
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
    GenericObjectFactory(){}
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

    IWorker* get(requestType type, std::shared_ptr<Connection> conn){
    }

private:
    GenericObjectFactory<requestType, IWorker, IHashTable*, ITableStorage*> factory;
};


#endif //MOND_DB_CONNECTIONWORKER_H
