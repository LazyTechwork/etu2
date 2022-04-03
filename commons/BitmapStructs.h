#pragma once
// To remove byte-padding from struct
#pragma pack(push)
#pragma pack(1)

#include <cstdint>

namespace BitmapStructs {

    struct Header {
        uint16_t Signature = 0x4D42;
        uint32_t FileSize{};
        uint16_t Reserved1 = 0;
        uint16_t Reserved2 = 0;
        uint32_t DataOffset{};
        uint32_t InfoHeaderSize = 40;
        int32_t Width{};
        int32_t Height{};
        uint16_t Planes = 1;
        uint16_t BitsPerPixel{};
        uint32_t Compression = 0;
        uint32_t ImageSize = 0;
        uint32_t XPPM = 0;
        uint32_t YPPM = 0;
        uint32_t ColorPaletteSize{};
        uint32_t ImportantColors = 0;

        Header(uint32_t fileSize, uint32_t dataOffset, int32_t width, int32_t height, uint16_t bitsPerPixel,
               uint32_t colorPaletteSize)
                : FileSize(fileSize), DataOffset(dataOffset), Width(width), Height(height),
                  BitsPerPixel(bitsPerPixel), ColorPaletteSize(colorPaletteSize) {}
    };

    struct Color {
        uint8_t Blue = 0;
        uint8_t Green = 0;
        uint8_t Red = 0;
        uint8_t X = 0;

        Color(uint8_t red, uint8_t green, uint8_t blue) : Red(red), Green(green), Blue(blue) {}

        Color() = default;
    };
}
#pragma pack(pop)