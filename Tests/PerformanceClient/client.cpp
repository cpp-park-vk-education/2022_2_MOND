// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"


class CommandsHandler {
 public:
    CommandsHandler(const std::string& host, uint16_t port) {
        try {
            actionManager = new ActionManager(host, port);
        } catch (...){

        }
    }

    void handleCommands() {
        std::string input;
        while(true){
            std::cout << "Input command: " << std::endl;
            std::cin >> input;
            if(input == "CREATE_TABLE"){
                std::string table_name;
                std::cin >> table_name;
                if(actionManager->CreateTable(table_name)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }
            if(input == "GET_TABLE"){
                std::string table_name;
                std::cin >> table_name;
                if(actionManager->SelectTable(table_name)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
            }

            if(input == "DELETE_TABLE"){
                std::string table_name;
                std::cin >> table_name;
                if(actionManager->DeleteTable(table_name)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
            }

            if(input == "INSERT"){
                std::string key, value;
                std::cin >> key;
                std::cin >> value;
                if(actionManager->Insert(key, value)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }

            if(input == "GET"){
                std::string key;
                std::cin >> key;
                auto ret = actionManager->Get(key);
                std::cout << ret << std::endl;
                continue;
            }

            if(input == "FIND"){
                std::string key;
                std::cin >> key;
                if(actionManager->Find(key)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }

            if(input == "UPDATE"){
                std::string key, value;
                std::cin >> key;
                std::cin >> value;
                if(actionManager->Update(key, value)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }

            if(input == "REMOVE"){
                std::string key, value;
                std::cin >> key;
                std::cin >> value;
                if(actionManager->Remove(key)){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }

            if(input == "CLEAR"){
                if(actionManager->Clear()){
                    std::cout << "SUCCESS" << std::endl;
                } else {
                    std::cout << "FAILURE" << std::endl;
                }
                continue;
            }

            if(input == "SHOW_TABLES"){
                std::cout << actionManager->GetTableNames() << std::endl;
                continue;
            }

            if(input == "QUIT"){
                break;
            }
        }
    }
    ~CommandsHandler() {
        delete actionManager;
    }

 private:
    IActionManager* actionManager;
};

int main(int argc, char** argv) {

    if (argc != 3){
        std::cout << "Wrong parameters." << std::endl;
        std::cout << "IP-address port" << std::endl;
        return 0;
    }

    CommandsHandler commandsHandler(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    commandsHandler.handleCommands();

    return 0;
}
