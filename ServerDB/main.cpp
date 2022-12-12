// Copyright 2022 MOND

#include "Initializer.h"

int main() {
    Initializer dataBase(5);
    dataBase.startDB();

    dataBase.handleCommands();

    dataBase.stopDB();
    return 0;
}
