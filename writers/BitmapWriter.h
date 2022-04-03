#pragma once

#include <string>

namespace BitmapWriter {
    void CreateBitmap(const std::string &filepath, uint8_t *data, const long &dataSize,
                      const int32_t &width,
                      const int32_t &height);
};
