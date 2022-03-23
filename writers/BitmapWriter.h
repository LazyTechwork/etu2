#pragma once

#include <string>

namespace BitmapWriter {
    struct BITMAPFILEHEADER {
        uint16_t bfType = 0x4D42;
        uint32_t bfSize;
        uint16_t bfReserved1 = 0;
        uint16_t bfReserved2 = 0;
        uint16_t bfOffBits;

        BITMAPFILEHEADER(uint32_t bfSize, uint16_t bfOffBits);
    };

    struct BITMAPINFO {
        uint32_t bcSize = 12;
        uint16_t bcWidth;
        uint16_t bcHeight;
        uint16_t bcPlanes = 1;
        uint16_t bcBitCount;

        BITMAPINFO(uint16_t bcWidth, uint16_t bcHeight, uint16_t bcBitCount);
    };

    void CreateBitmap(const std::string& filepath, uint8_t *data, unsigned int dataSize,
                      uint16_t width,
                      uint16_t height,
                      uint32_t customDataSize = 0, uint8_t *customData = nullptr);
};
