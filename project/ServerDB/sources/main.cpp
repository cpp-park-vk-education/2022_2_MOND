// Copyright 2022 MOND

#include <iostream>

#include "Connector.hpp"
#include "header.hpp"

int main() {
    Connector conn;
    std::cout << sum(1, 2) << " " << conn.mul(1, 2) << std::endl;
    return 0;
}
