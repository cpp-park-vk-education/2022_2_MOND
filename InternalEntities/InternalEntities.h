// Copyright 2022 mora

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

enum class requestType {
    INSERT = 0,
    REMOVE,
    FIND,
    CLEAR,
    GET_SIZE,
    GET,
    UPDATE,
    CREATE_TABLE = 100,
    DELETE_TABLE,
    GET_TABLE,
    GET_NUM_TABLES,
    SHOW_TABLES,
    DEFAULT
};

enum class Status { NOTHING = 0, READY, WORKING, OK, FAILURE };

class Request {
 public:
    Request() = default;
    Request(const requestType&, const Status&, const std::vector<uint8_t>&,
            const std::vector<uint8_t>&, const std::string&);
    Request(const Request&) = default;
    Request(Request&&) noexcept;
    ~Request()= default;

    Request& operator=(const Request&);
    Request& operator=(Request&&) noexcept;
    bool operator==(const Request& other) const;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);
    void save(std::ostream& oss) const;
    void load(const std::string& str_data);

 private:
    requestType _type = requestType::DEFAULT;
    Status _status = Status::FAILURE;
    std::vector<uint8_t> _key;
    std::vector<uint8_t> _value;
    std::string _table_name;
};

Request::Request(Request&& other) noexcept
    : _type(other._type),
      _status(other._status),
      _key(other._key),
      _value(other._value),
      _table_name(other._table_name) {}

Request& Request::operator=(const Request& other) {
    if (&other == this) {
        return *this;
    }

    _type = other._type;
    _status = other._status;
    _key = other._key;
    _value = other._value;
    _table_name = other._table_name;
    return *this;
}

Request& Request::operator=(Request&& other) noexcept { return *this = other; }

Request::Request(const requestType& type, const Status& status,
                 const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& value,
                 const std::string& table_name)
    : _type(type),
      _status(status),
      _key(key),
      _value(value),
      _table_name(table_name) {}

template <class Archive>
void Request::serialize(Archive& ar, const unsigned int version) {
    ar & _type;
    ar & _status;
    ar & _key;
    ar & _value;
    ar & _table_name;
}

bool Request::operator==(const Request& other) const {
    return _type == other._type && _status == other._status &&
           _key == other._key && _value == other._value &&
           _table_name == other._table_name;
}

void Request::save(std::ostream& oss) const {
    boost::archive::binary_oarchive oa(oss);
    oa & *(this);
}

void Request::load(const std::string& str_data) {
    std::istringstream iss(str_data);
    boost::archive::binary_iarchive ia(iss);
    ia & *(this);
}

BOOST_CLASS_VERSION(Request, 1)
