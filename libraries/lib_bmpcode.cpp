#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include "../cli_tools/ArgsParser.h"
#include "../writers/BitmapWriter.h"

int main(int argc, char *argv[]) {
    setlocale(0, "ru_RU.utf8");
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    auto args = ArgsParser(argc, argv);
    std::string filename;
    bool encode = false;
    if (args.has("encode")) {
        filename = args.get("encode");
        encode = true;
    } else if (args.has("e")) {
        filename = args.get("e");
        encode = true;
    } else if (args.has("decode")) {
        filename = args.get("decode");
    } else if (args.has("d")) {
        filename = args.get("d");
    } else {
        std::cout << "Insufficient arguments (expected 2)" << std::endl;
        return -1;
    }

    if (encode) {
        FILE *file = fopen(filename.c_str(), "rb");

        if (file == nullptr) {
            std::wcout << "Cannot open file at " << filename.c_str() << std::endl;
            exit(-1);
        }

//        Seeking for the end of the file
        fseek(file, 0, SEEK_END);
        auto file_size = ftell(file);

//        Setting seek cursor at the start of the file
        fseek(file, 0, SEEK_SET);

//        Allocating memory for data
        auto *data = new uint8_t[file_size];
//        Filling zeroes
        memset(data, 0, sizeof(uint8_t) * file_size);
//        Reading all file to memory
        fread(data, sizeof(uint8_t), file_size, file);
//        Closing file
        fclose(file);

        const unsigned int bmp_side = ceil(sqrt(file_size));
        BitmapWriter::CreateBitmap(filename + ".bmp", data, file_size, bmp_side, bmp_side);
    }
    _getch();
    return 0;
}
