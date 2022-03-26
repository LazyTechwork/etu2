#include <iostream>
#include <cmath>
#include "BitmapWriter.h"
#include "../commons/BitmapStructs.h"

void BitmapWriter::CreateBitmap(
        const std::string &filepath, uint8_t *data, const long &dataSize,
        const uint16_t &width,
        const uint16_t &height
) {
    FILE *file = fopen(filepath.c_str(), "wb");
    if (file == nullptr) {
        std::wcout << "Cannot open file at " << filepath.c_str() << std::endl;
        exit(-1);
    }

    const auto bmp_row_size = (int) ceil(width / 4.0) * 4;

    auto *header = new BitmapStructs::Header{
            (uint32_t) (bmp_row_size * height + sizeof(BitmapStructs::Header) +
                        (1 << 8) * sizeof(BitmapStructs::Color)),
            sizeof(BitmapStructs::Header) + (1 << 8) * sizeof(BitmapStructs::Color),
            width,
            height,
            8,
            (1 << 8)
    };
    fwrite(header, sizeof(BitmapStructs::Header), 1, file);
    delete header;

//    Generating palette
    BitmapStructs::Color *color;
    for (int i = 0, l = (1 << 8) - 1; i <= l; ++i) {
        color = new BitmapStructs::Color{(uint8_t) i, (uint8_t) i, (uint8_t) i};
        fwrite(color, sizeof(BitmapStructs::Color), 1, file);
    }
    delete color;

    const uint8_t *nullbyte = new uint8_t(0);
    unsigned int rows_written = 0;

    for (int i = 0; i < dataSize; i += width) {
//        Writing data byte-by-byte
        for (int j = 0; j < width; ++j)
            if (i + j > dataSize) {
                fwrite(nullbyte, 1, sizeof(uint8_t), file);
                printf("00 ");
            } else {
                fwrite(data + i + j, 1, sizeof(uint8_t), file);
                printf("%02X ", *(data + i + j));
            }

//        Writing paddings
        for (int j = 0, l = bmp_row_size - width; j < l; ++j) {
            fwrite(nullbyte, 1, sizeof(uint8_t), file);
            printf("00 ");
        }
        ++rows_written;
        printf("\n");
    }

//    Creating zero-rows to complete height
    for (unsigned int i = 0, l = height - rows_written; i < l; ++i) {
        for (int j = 0; j < bmp_row_size; ++j) {
            fwrite(nullbyte, 1, sizeof(uint8_t), file);
            printf("00 ");
        }
        printf("\n");
    }

    fclose(file);
}
