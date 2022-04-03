#include <iostream>
#include <cmath>
#include "BitmapWriter.h"
#include "../commons/BitmapStructs.h"
#include "../cli_tools/Loader.h"

const auto *NULL_BYTE = new uint8_t(0);

void BitmapWriter::CreateBitmap(
        const std::string &filepath, uint8_t *data, const long &dataSize,
        const int32_t &width,
        const int32_t &height
) {
    FILE *file = fopen(filepath.c_str(), "wb");
    if (file == nullptr) {
        std::wcout << "Cannot open file at " << filepath.c_str() << std::endl;
        exit(-1);
    }

    auto *loader = new Loader(L"Generating BMP file");

    const uint32_t bmp_row_size = (uint32_t) ceil(width / 4.0) * 4;

    auto *header = new BitmapStructs::Header{
            (uint32_t) (bmp_row_size * height + sizeof(BitmapStructs::Header) +
                        (1 << 8) * sizeof(BitmapStructs::Color)),
            sizeof(BitmapStructs::Header) + (1 << 8) * sizeof(BitmapStructs::Color),
            width,
            height,
            8,
            (1 << 8)
    };

    fwrite(&header->Signature, sizeof(BitmapStructs::Header::Signature), 1, file);
    fwrite(&header->FileSize, sizeof(BitmapStructs::Header::FileSize), 1, file);
    fwrite(&header->Reserved1, sizeof(BitmapStructs::Header::Reserved1), 1, file);
    fwrite(&header->Reserved2, sizeof(BitmapStructs::Header::Reserved2), 1, file);
    fwrite(&header->DataOffset, sizeof(BitmapStructs::Header::DataOffset), 1, file);
    fwrite(&header->InfoHeaderSize, sizeof(BitmapStructs::Header::InfoHeaderSize), 1, file);
    fwrite(&header->Width, sizeof(BitmapStructs::Header::Width), 1, file);
    fwrite(&header->Height, sizeof(BitmapStructs::Header::Height), 1, file);
    fwrite(&header->Planes, sizeof(BitmapStructs::Header::Planes), 1, file);
    fwrite(&header->BitsPerPixel, sizeof(BitmapStructs::Header::BitsPerPixel), 1, file);
    fwrite(&header->Compression, sizeof(BitmapStructs::Header::Compression), 1, file);
    fwrite(&header->ImageSize, sizeof(BitmapStructs::Header::ImageSize), 1, file);
    fwrite(&header->XPPM, sizeof(BitmapStructs::Header::XPPM), 1, file);
    fwrite(&header->YPPM, sizeof(BitmapStructs::Header::YPPM), 1, file);
    fwrite(&header->ColorPaletteSize, sizeof(BitmapStructs::Header::ColorPaletteSize), 1, file);
    fwrite(&header->ImportantColors, sizeof(BitmapStructs::Header::ImportantColors), 1, file);

//    Generating palette
    BitmapStructs::Color *color;
    for (int i = 0, l = (1 << 8) - 1; i <= l; ++i) {
        color = new BitmapStructs::Color{(uint8_t) i, (uint8_t) i, (uint8_t) i};
        fwrite(color, sizeof(BitmapStructs::Color), 1, file);
    }
    delete color;

    unsigned int rows_written = 0;

    for (int i = 0; i < dataSize; i += width) {
//        Writing data byte-by-byte
        for (int j = 0; j < width; ++j)
            if (i + j > dataSize)
                fwrite(NULL_BYTE, 1, 1, file);
            else
                fwrite(data + i + j, 1, 1, file);

//        Writing paddings
        for (int j = 0, l = (int) bmp_row_size - width; j < l; ++j)
            fwrite(NULL_BYTE, 1, 1, file);

        ++rows_written;
        if (i % 7 == 0)
            loader->loop();
    }

//    Creating zero-rows to complete height
    for (unsigned int i = 0, l = height - rows_written; i < l; ++i)
        for (int j = 0; j < bmp_row_size; ++j)
            fwrite(NULL_BYTE, 1, sizeof(uint8_t), file);

    fclose(file);
    loader->stop();
    std::cout << "Written BMP file: " << width << "x" << height << "px - " << header->FileSize << "B" << std::flush;
    delete loader;
    delete header;
}
