#pragma once

#include <string>
#include <list>
#include <Windows.h>
#include <vector>

class FilesystemReader {
public:
    static void readFilesInDirectory(std::string path, std::vector<WIN32_FIND_DATA> &files);

    static bool isDirectory(WIN32_FIND_DATA &file);
};
