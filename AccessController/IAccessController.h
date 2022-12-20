//
// Created by John on 19.12.2022.
//

#ifndef MOND_DB_I_ACCESS_CONTOLLER_H
#define MOND_DB_I_ACCESS_CONTOLLER_H

#include "InternalEntities.h"

class IAccessController {
 public:
    virtual void getPermission(const std::shared_ptr<Request> &request) = 0;
    virtual void releaseResource(const std::shared_ptr<Request> &request) = 0;
    virtual ~IAccessController() = default;
};

#endif //MOND_DB_I_ACCESS_CONTOLLER_H
