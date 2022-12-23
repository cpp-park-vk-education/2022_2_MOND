// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"


void test(int argc, char** argv){

    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    std::cout << "connection established" << std::endl;
    std::string input;

    while(true){
        std::cout << "Input command: " << std::endl;
        std::cin >> input;
        if(input == "CREATE_TABLE"){
            std::string table_name;
            std::cin >> table_name;
            if(manager->CreateTable(table_name)){
                std::cout << "SUCCESS" << std::endl;
            } else {
                std::cout << "FAILURE" << std::endl;
            }
            continue;
        }
        if(input == "GET_TABLE"){
            std::string table_name;
            std::cin >> table_name;
            if(manager->SelectTable(table_name)){
                std::cout << "SUCCESS" << std::endl;
            } else {
                std::cout << "FAILURE" << std::endl;
            }
        }

        if(input == "INSERT"){
            std::string key, value;
            std::cin >> key;
            std::cin >> value;
            if(manager->Insert(key, value)){
                std::cout << "SUCCESS" << std::endl;
            } else {
                std::cout << "FAILURE" << std::endl;
            }
            continue;
        }

        if(input == "GET"){
            std::string key, value;
            std::cin >> key;
            auto ret = manager->Get(key);
            std::cout << ret << std::endl;
            continue;
        }

        if(input == "QUIT"){
            break;
        }
    }

    delete manager;
}

int main(int argc, char** argv) {
    test(argc, argv);
    return 0;
}
