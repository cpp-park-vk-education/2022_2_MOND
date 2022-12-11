// Copyright 2022 MOND

#include "Initializer.h"

int main() {
    Initializer dataBase;
    dataBase.startDB(2);
    dataBase.handleCommands();
    dataBase.stopDB();
    return 0;
}
