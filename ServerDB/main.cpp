// Copyright 2022 MOND

#include "Initializer.h"

int main() {
    Initializer dataBase;
    dataBase.startDB(1);

    std::cout << std::thread::hardware_concurrency() << std::endl;

    dataBase.handleCommands();
    dataBase.stopDB();
    return 0;
}
