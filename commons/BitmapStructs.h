#pragma once

#include <cstdint>

namespace BitmapStructs {
    struct Header {
        uint16_t Signature = 0x424D;
        uint32_t FileSize;
        uint32_t Reserved;
        uint32_t DataOffset;
        uint32_t InfoHeaderSize = 12;
        uint16_t Width;
        uint16_t Height;
        uint16_t Planes = 1;
        uint16_t BitsPerPixel;
    };
}