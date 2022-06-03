#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include "readers/FilesystemReader.h"
#include "terminal/Keyboard.h"

#define HIGHLIGHTED_TEXT 112
#define STANDART_TEXT 15

int main(int argc, char *argv[]) {
    setlocale(0, "ru_RU.utf8");
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    std::string current_directory = R"(C:\)";
    TCHAR curDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, curDir);
    current_directory = std::string(curDir) + std::string("\\");
    const std::string libraries_path(current_directory);
    const std::string lib_wave = current_directory + "lib_wave.exe";
    const std::string lib_bmpcode = current_directory + "lib_bmpcode.exe";
    const std::string lib_bytelysis = current_directory + "lib_bytelysis.exe";
    int key = -1, selectedFile;
    COORD selectedFileConsolePos;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::vector<WIN32_FIND_DATA> directoryListing;
    bool isDirectoryDirty = true;

    do {
        if (key != -1)
            if (key == ARROW_PREFIX) {
                switch ((key = _getch())) {
                    case ARROW_DOWN:
                        ++selectedFile;
                        if (selectedFile >= directoryListing.size())
                            selectedFile = 0;
                        break;
                    case ARROW_UP:
                        --selectedFile;
                        if (selectedFile < 0)
                            selectedFile = directoryListing.size() - 1;
                        break;
                }
            } else if (key == FUNC_PREFIX) {
                switch ((key = _getch())) {
                    case FUNC_1:
                        if (!FilesystemReader::isDirectory(directoryListing[selectedFile])) {
                            std::string command = R"(start "" ")";
                            command
                                    .append(lib_wave)
                                    .append("\" \"")
                                    .append(current_directory)
                                    .append(directoryListing[selectedFile].cFileName)
                                    .append("\"");
                            system(command.c_str());
                        }
                        break;
                    case FUNC_2:
                        if (!FilesystemReader::isDirectory(directoryListing[selectedFile])) {
                            std::string command = R"(start "" ")";
                            command
                                    .append(lib_bmpcode)
                                    .append("\" -encode \"")
                                    .append(current_directory)
                                    .append(directoryListing[selectedFile].cFileName)
                                    .append("\"");
                            system(command.c_str());
                        }
                        break;
                    case FUNC_3:
                        if (!FilesystemReader::isDirectory(directoryListing[selectedFile])) {
                            system("cls");
                            std::cout << std::endl << "Make byte analysis" << std::endl
                                      << "Enter lower value (float 0-1): ";
                            float arg;
                            std::cin >> arg;
                            std::string command = R"(start "" ")";
                            command
                                    .append(lib_bytelysis)
                                    .append("\" \"")
                                    .append(current_directory)
                                    .append(directoryListing[selectedFile].cFileName)
                                    .append("\" --tr ")
                                    .append(std::to_string(arg));
                            system(command.c_str());
                            std::cout << std::endl;
                        }
                        break;
                }
            } else if (key == KEY_RETURN) {
                if (FilesystemReader::isDirectory(directoryListing[selectedFile])) {
                    SetCurrentDirectory(
                            std::string(current_directory + directoryListing[selectedFile].cFileName).c_str());
                    GetCurrentDirectory(MAX_PATH, curDir);
                    current_directory = std::string(curDir) + std::string("\\");
                    isDirectoryDirty = true;
                } else {
                    std::string command = R"(start "" ")";
                    command
                            .append(current_directory)
                            .append(directoryListing[selectedFile].cFileName)
                            .append("\"");
                    system(command.c_str());
                }
            } else if (key == CTRL_R) {
                isDirectoryDirty = true;
            } else if (key == CTRL_C) {
                return 0;
            }
        GetConsoleScreenBufferInfo(stdHandle, &csbiInfo);
        system("cls");

        // Update directory listing if needed
        if (isDirectoryDirty) {
            directoryListing.erase(directoryListing.begin(), directoryListing.end());
            FilesystemReader::readFilesInDirectory(current_directory + "*", directoryListing);
            selectedFile = 0;
            isDirectoryDirty = false;
        }

        // === Render manager ===

        // Render up menu
        std::cout << " ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " F1 ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Analyse WAV file ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " F2 ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Convert to BMP ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " F3 ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Analyse bytes ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " ENTER ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Open ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " ^R ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Reload ";
        SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
        std::cout << " ^C ";
        SetConsoleTextAttribute(stdHandle, STANDART_TEXT);
        std::cout << " Quit ";
        std::cout << std::endl << std::endl << "Current directory: " << current_directory << std::endl << std::endl;

        for (int i = 0, entriesTotal = directoryListing.size(); i < entriesTotal; ++i) {
            std::cout << " ";

            if (i == selectedFile) {
                SetConsoleTextAttribute(stdHandle, HIGHLIGHTED_TEXT);
                GetConsoleScreenBufferInfo(stdHandle, &csbiInfo);
                selectedFileConsolePos = csbiInfo.dwCursorPosition;
            }

            WIN32_FIND_DATA file = directoryListing[i];
            bool isDir = FilesystemReader::isDirectory(file);
            std::cout << file.cFileName << (isDir ? "\\" : "");

            if (i == selectedFile)
                SetConsoleTextAttribute(stdHandle, STANDART_TEXT);

            std::cout << std::endl;
        }

        SetConsoleCursorPosition(stdHandle, selectedFileConsolePos);
        key = _getch();
    } while (true);
}
