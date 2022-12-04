// Copyright 2022 mora

#pragma once

#include "InternalEntities.h"

//#include <boost/thread.h>
#include <iostream>

class ISerializer {
public:
    virtual uint8_t * Marshal(Request) = 0;

    virtual Request Unmarshal(const uint8_t *) = 0;

    virtual ~ISerializer() = default;
};
