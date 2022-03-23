#include <iostream>
#include <cstring>
#include <cmath>
#include "../cli_tools/ArgsParser.h"
#include "../writers/BitmapWriter.h"

int main(int argc, char *argv[]) {
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

    FILE *file = fopen("C:\\Users\\LazyTechwork\\Dev\\etu2\\test.bmp", "rb");
    BitmapWriter::BITMAPFILEHEADER bitmapfileheader{0, 0};
    BitmapWriter::BITMAPINFO bitmapinfo{0, 0, 0};
    fread(&bitmapfileheader, sizeof(bitmapfileheader), 1, file);
    fread(&bitmapinfo, sizeof(bitmapinfo), 1, file);
    fclose(file);
    return 0;
}
