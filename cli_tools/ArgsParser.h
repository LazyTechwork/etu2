#pragma once


#include <string>
#include <map>

class ArgsParser {
    int count;
    std::map<std::string, std::string> *arguments;

public:
    ArgsParser(int argc, char *argv[]);

    std::string get(const std::string& key);
    bool has(const std::string& key);
};
