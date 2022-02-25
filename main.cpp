#include <iostream>
#include <numeric>
#include "readers/WaveReader.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not found file in passed arguments");
        return -1;
    }

    WaveReader reader(argv[1], true);
    auto cas = reader.GetComplexAmplitudes(200, 800);

    const int histogram[]{50, 100, 1000, 2000, 5000, 10000, 20000};
    const auto ComplexAbsoluteAccumulate = [&](coamp a, coamp b) {
        return std::abs(a) + std::abs(b);
    };

    for (int hId = 0; hId < 7; ++hId) {
        int h = histogram[hId];
        int hStart = hId != 0 ? histogram[hId - 1] : 0;
        printf(
                "%dHz: %f \n", h,
                std::accumulate(cas.begin() + hStart,
                                cas.begin() + h,
                                0.0,
                                ComplexAbsoluteAccumulate)
                / (h - hStart)
        );
    }

    return 0;
}
