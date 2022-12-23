//
// Created by John on 19.12.2022.
//

#ifndef MOND_DB_TESTS_ACTIONMANAGER_H
#define MOND_DB_TESTS_ACTIONMANAGER_H

#include <future>
#include "AccessController.h"

#define TEST_TIMEOUT_BEGIN   std::promise<bool> promisedFinished; \
                              auto futureResult = promisedFinished.get_future(); \
                              std::thread([this](std::promise<bool>& finished) {

#define TEST_TIMEOUT_FAIL_END(X)  finished.set_value(true); \
                                   }, std::ref(promisedFinished)).detach(); \
                                   EXPECT_TRUE(futureResult.wait_for(std::chrono::milliseconds(X)) != std::future_status::timeout);

#define TEST_TIMEOUT_SUCCESS_END(X)  finished.set_value(true); \
                                      }, std::ref(promisedFinished)).detach(); \
                                      EXPECT_FALSE(futureResult.wait_for(std::chrono::milliseconds(X)) != std::future_status::timeout);

class ActionManagerTimeout: public testing::Test {
protected:
    void SetUp() override{
        for (size_t i = 0; i < 100; ++i) {
            read_requests.push_back(std::make_shared<Request>());
            read_requests[i]->_table_name = "Testing";
            read_requests[i]->_type = RequestType::GET;
        }

        for (size_t i = 0; i < 100; ++i) {
            write_requests.push_back(std::make_shared<Request>());
            write_requests[i]->_table_name = "Testing";
            write_requests[i]->_type = RequestType::INSERT;
        }
    }

 public:
    AccessController controller;
    std::vector<std::shared_ptr<Request>> read_requests;
    std::vector<std::shared_ptr<Request>> write_requests;
};

TEST_F(ActionManagerTimeout, withOneThread) {
    TEST_TIMEOUT_BEGIN

    auto initializationRequest = std::make_shared<Request>();
    initializationRequest->_table_name = "Testing";
    initializationRequest->_type = RequestType::CREATE_TABLE;
    controller.getPermission(initializationRequest);
    controller.releaseResource(initializationRequest);

    for(const auto& iter: read_requests){
        controller.getPermission(iter);
    }

    for(const auto& iter: read_requests){
        controller.releaseResource(iter);
    }

    for (const auto &iter: write_requests) {
        controller.getPermission(iter);
        controller.releaseResource(iter);
    }

    TEST_TIMEOUT_FAIL_END(1000)
}

TEST_F(ActionManagerTimeout, withTwoThreads) {
    TEST_TIMEOUT_BEGIN

    auto initializationRequest = std::make_shared<Request>();
    initializationRequest->_table_name = "Testing";
    initializationRequest->_type = RequestType::CREATE_TABLE;
    controller.getPermission(initializationRequest);
    controller.releaseResource(initializationRequest);

    std::thread t1([&] {
        for(const auto& iter: read_requests){
            controller.getPermission(iter);
        }

        for(const auto& iter: read_requests){
            controller.releaseResource(iter);
        }
    });

    std::thread t2([&] {
        for(const auto& iter: write_requests){
            controller.getPermission(iter);
            controller.releaseResource(iter);
        }
    });

    t1.join();
    t2.join();

    TEST_TIMEOUT_FAIL_END(1000)
}

#endif //MOND_DB_TESTS_ACTIONMANAGER_H
