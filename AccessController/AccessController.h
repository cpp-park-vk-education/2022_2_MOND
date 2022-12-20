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

}

void AccessController::releaseResource(const std::shared_ptr<Request> &request) {

}

#endif //  MOND_DB_ACCESS_CONTROLLER_H
