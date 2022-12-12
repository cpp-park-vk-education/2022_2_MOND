// Copyright 2022 MOND

#include "Initializer.h"

int main() {
    Initializer dataBase(1);
    dataBase.startDB();

    dataBase.handleCommands();

    dataBase.stopDB();
    return 0;
}
