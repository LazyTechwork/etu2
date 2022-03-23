#include "ArgsParser.h"

ArgsParser::ArgsParser(int argc, char *argv[]) {
    this->count = argc;
    this->arguments = new std::map<std::string, std::string>;
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] != '-')
            continue;
        auto key = std::string(argv[i]).substr(argv[i][1] == '-' ? 2 : 1);
        auto value = std::string(argv[++i]);
        this->arguments->insert(std::make_pair(key, value));
    }
}

std::string ArgsParser::get(const std::string& key) {
    if (this->has(key))
        return this->arguments->at(key);
    else
        return "";
}

bool ArgsParser::has(const std::string &key) {
    return this->arguments->count(key);
}
