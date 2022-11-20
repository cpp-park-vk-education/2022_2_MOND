// Copyright 2022 mora

#pragma once

#include <iostream>
#include "InternalEntities.h"

class ISerializer {
public:
    virtual uint8_t * Marshal(Request) = 0;

    virtual Request Unmarshal(uint8_t *) = 0;

    virtual ~ISerializer() = default;
};
