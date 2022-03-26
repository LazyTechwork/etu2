#pragma once

#include <string>

namespace BitmapWriter {
    void CreateBitmap(const std::string &filepath, uint8_t *data, const long &dataSize,
                      const uint16_t &width,
                      const uint16_t &height);
};
