#pragma once

#define HISTOGRAM_BAR (wchar_t) 219
#define HISTOGRAM_SPACE L' '
#define HISTOGRAM_FRAME_VERTICAL (wchar_t) 179
#define HISTOGRAM_FRAME_CROSS (wchar_t) 197
#define HISTOGRAM_FRAME_HORIZONTAL (wchar_t) 196

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>

namespace Terminal {
    void printHistogram(int *header, double *data, unsigned int count, double min, double max, double step);
}

