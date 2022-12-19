// Copyright 2022 mora

#ifndef MOND_DB_BACKUPPER_H
#define MOND_DB_BACKUPPER_H

#include "IBackupper.h"

#include <fstream>

class Backupper : public IBackupper {
public:
    void SetPath(const  boost::filesystem::path &path) override;
    [[nodiscard]] bool MakeBackup(const Request &rqst) const override;
    [[nodiscard]] std::vector<Request> ReadBackup() const override;

private:
//    boost::filesystem::path _path = boost::filesystem::current_path();
    boost::filesystem::path _path = "/tmp";
};

void Backupper::SetPath(const boost::filesystem::path &path) {
    _path = path;
}

bool Backupper::MakeBackup(const Request &rqst) const {
    boost::asio::streambuf buff;
    std::ostream oss(&buff);

    rqst.save(oss);

    boost::filesystem::ofstream out;

    out.open(_path / "backup.mdb", boost::filesystem::ofstream::out | boost::filesystem::ofstream::app);
    if (out) {
        out << oss.rdbuf();
    } else {
        return false;
    }
    out.close();
    return true;
}

std::vector<std::string> split(const std::string& str, const std::string& del){
    std::vector<std::string> v;
    if (!str.empty()) {
        size_t start = 0;
        do {
            auto idx = str.find(del, start);
            if (idx == std::string::npos) {
                break;
            }
            size_t length = idx - start;
            v.push_back(str.substr(start, length + del.size()));
            start += (length + del.size());
        } while (true);
    }
    return v;
}

std::vector<Request> Backupper::ReadBackup() const {
    std::vector<Request> result;
    boost::asio::streambuf buff;
    std::ostream oss(&buff);

    boost::filesystem::ifstream in;
    in.open(_path / "backup.mdb", std::ios::in);

    if(in){
        in >> oss.rdbuf();
        std::stringstream ss;
        ss << oss.rdbuf();
        std::vector<std::string> str_requests = split(ss.str(), delimiter);

        for(auto &it : str_requests){
            Request rqst;
            rqst.load(it);
            result.push_back(rqst);
        }
    }else{
        return {};
    }

    return result;
}

#endif//MOND_DB_BACKUPPER_H
