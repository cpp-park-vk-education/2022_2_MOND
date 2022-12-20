//
// Created by John on 19.12.2022.
//

#ifndef MOND_DB_ACCESS_CONTROLLER_H
#define MOND_DB_ACCESS_CONTROLLER_H

#include "IAccessController.h"

#include <queue>

class AccessController: public IAccessController {
 public:
    void getPermission(const std::shared_ptr<Request> &request) override;
    void releaseResource(const std::shared_ptr<Request> &request) override;

 private:
    struct ControlNode {
        std::queue<std::shared_ptr<Request>> requestIndexes;
        std::mutex requestIndexesMutex;
        std::atomic<size_t> readers = 0;
    };

    std::unordered_map<std::string, std::shared_ptr<ControlNode>> controlMap;
};

void AccessController::getPermission(const std::shared_ptr<Request> &request) {

    if(request->_type == RequestType::CREATE_TABLE){
        controlMap.insert(std::make_pair(request->_table_name, std::make_shared<ControlNode>()));
        return;
    }

    auto tableControl = controlMap[request->_table_name];

    tableControl->requestIndexesMutex.lock();
    tableControl->requestIndexes.push(request);
    tableControl->requestIndexesMutex.unlock();

    while (!(tableControl->requestIndexes.front() == request)) {}
    if (request->isChangingData()) {
        while (tableControl->readers != 0) {}
    } else {

        tableControl->readers++;

        tableControl->requestIndexesMutex.lock();
        tableControl->requestIndexes.pop();
        tableControl->requestIndexesMutex.unlock();
    }
}

void AccessController::releaseResource(const std::shared_ptr<Request> &request) {
    if(request->_type == RequestType::CREATE_TABLE){
        return;
    }
    auto tableControl = controlMap[request->_table_name];
    if(request->isChangingData()){
        tableControl->requestIndexesMutex.lock();
        tableControl->requestIndexes.pop();
        tableControl->requestIndexesMutex.unlock();
    } else {
        tableControl->readers--;
    }
}

#endif //  MOND_DB_ACCESS_CONTROLLER_H
