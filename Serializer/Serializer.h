// Copyright 2022 mora

#ifndef MOND_DB_SERIALIZER_H
#define MOND_DB_SERIALIZER_H

#include "ISerializer.h"

class Serializer : public ISerializer {
private:

public:
    Serializer();

    uint8_t * Marshal(Request);

    Request Unmarshal(const uint8_t *);

    ~Serializer();
};

#endif //MOND_DB_SERIALIZER_H
