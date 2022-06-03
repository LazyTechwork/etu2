#include <iostream>
#include "FilesystemReader.h"

void FilesystemReader::readFilesInDirectory(std::string path, std::vector<WIN32_FIND_DATA> &files) {
    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile(path.c_str(), &fileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "Cannot open directory";
        return;
    }
    do {
        files.push_back(fileData);
    } while (FindNextFile(hFind, &fileData));
    FindClose(hFind);
}

bool FilesystemReader::isDirectory(WIN32_FIND_DATA &file) {
    return file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}
