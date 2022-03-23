#include <iostream>
#include "BitmapWriter.h"

void BitmapWriter::CreateBitmap(const std::string &filepath, uint8_t *data, unsigned int dataSize,
                                uint16_t width,
                                uint16_t height,
                                uint32_t customDataSize, uint8_t *customData) {
    FILE *file = fopen(filepath.c_str(), "wb");
    if (file == nullptr) {
        std::wcout << "Cannot open file at " << filepath.c_str() << std::endl;
        exit(-1);
    }
    BITMAPFILEHEADER bmpHeader{
            static_cast<uint32_t>((sizeof(BITMAPFILEHEADER)) + (sizeof(BITMAPINFO)) + customDataSize + dataSize),
            static_cast<uint16_t>(customDataSize + 1)};
    BITMAPINFO bmpInfo{width, height, 8};
    fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(&bmpInfo, sizeof(BITMAPINFO), 1, file);
    if (customDataSize > 0)
        fwrite(customData, sizeof(uint8_t), customDataSize, file);
    fwrite(data, sizeof(uint8_t), dataSize, file);
    fclose(file);
//    const uint32_t rowSize = (uint32_t) ceil((bmpInfo.bcBitCount * width) / 32.0) * 4;
}

BitmapWriter::BITMAPFILEHEADER::BITMAPFILEHEADER(uint32_t bfSize, uint16_t bfOffBits) : bfSize(bfSize), bfOffBits(bfOffBits) {}

BitmapWriter::BITMAPINFO::BITMAPINFO(uint16_t bcWidth, uint16_t bcHeight, uint16_t bcBitCount) : bcWidth(bcWidth), bcHeight(bcHeight),
                                                                                   bcBitCount(bcBitCount) {}
