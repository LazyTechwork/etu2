#pragma once

#include <string>

namespace BitmapWriter {
    void CreateBitmap(const std::string &filepath, uint8_t *data, unsigned int dataSize,
                      uint16_t width, uint16_t height);
};
