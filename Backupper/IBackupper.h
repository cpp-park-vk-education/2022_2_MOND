// Copyright 2022 MOND

#ifndef MOND_DB_IBACKUPPER_H
#define MOND_DB_IBACKUPPER_H

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/serialization/map.hpp>

#include "regex"

#include "InternalEntities.h"

class IBackupper{
public:
    virtual void SetPath(const boost::filesystem::path &path) = 0;
    [[nodiscard]] virtual bool MakeBackup(const Request &rqst) const = 0;
    [[nodiscard]] virtual std::vector<Request> ReadBackup() const = 0;

    virtual ~IBackupper() = default;
};
#endif//MOND_DB_IBACKUPPER_H
