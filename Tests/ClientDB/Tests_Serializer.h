// Copyright 2022 mora

#include "help_for_tests.h"


class Request_Serializer : public testing::Test {
protected:
    void SetUp() override {
        req = {requestType::INSERT, Status::NOTHING, key, value, table_name};
    }

    Request req;
    std::vector<uint8_t> key = {0x01, 0x02};
    std::vector<uint8_t> value = {0x03, 0x04, 0x05};
    std::string table_name = "Table01";
};

TEST_F(Request_Serializer, Marshal_Success) {
    boost::asio::streambuf buf;
    std::ostream oss(&buf);

    req.save(oss);

    EXPECT_EQ(buf.size() - 4, sizeof(req) + 1);
}

TEST_F(Request_Serializer, Unmarshal_Success) {
    boost::asio::streambuf buf;
    std::ostream oss(&buf);

    req.save(oss);

    std::stringstream ss;
    ss << oss.rdbuf();
    std::string str_data = ss.str();

    Request req_test;

    req_test.load(str_data);
    EXPECT_EQ(req, req_test);
}
