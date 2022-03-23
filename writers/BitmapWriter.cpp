#include <iostream>
#include "BitmapWriter.h"

void BitmapWriter::CreateBitmap(const std::string &filepath, uint8_t *data, unsigned int dataSize, uint16_t width,
                                uint16_t height) {
    FILE *file = fopen(filepath.c_str(), "wb");
    if (file == nullptr) {
        std::wcout << "Cannot open file at " << filepath.c_str() << std::endl;
        exit(-1);
    }
//    fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(data, sizeof(uint8_t), dataSize, file);
    fclose(file);
//    const uint32_t rowSize = (uint32_t) ceil((bmpInfo.bcBitCount * width) / 32.0) * 4;
}
