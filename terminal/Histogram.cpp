#include "Histogram.h"

void Terminal::printHistogram(int *header, double *data, unsigned int count,
                              double min, double max, double step) {
    using namespace std;

    unsigned int spacePerColumn = to_wstring(*max_element(header, header + count)).length() + 2;
    auto barSpace = wstring((unsigned int) ((spacePerColumn - 2) / 2.0), HISTOGRAM_SPACE);

    wcout << fixed << setprecision(2);
    wcout << wstring(7, HISTOGRAM_SPACE) << HISTOGRAM_FRAME_VERTICAL << endl;
    for (double y = max; y >= min; y -= step) {
        wcout.width(6);
        wcout << y << HISTOGRAM_SPACE << HISTOGRAM_FRAME_VERTICAL << HISTOGRAM_SPACE;
        for (int x = 0; x < count; ++x) {
            auto bar = data[x] > y ?
                       wstring(2, HISTOGRAM_BAR) : wstring(2, HISTOGRAM_SPACE);
            wcout << barSpace << bar << barSpace;
        }
        wcout << endl;
    }
    wcout << wstring(7, HISTOGRAM_SPACE) << HISTOGRAM_FRAME_CROSS
          << wstring(spacePerColumn * count, HISTOGRAM_FRAME_HORIZONTAL) << endl;
    wcout << wstring(9, HISTOGRAM_SPACE);
    for (int i = 0; i < count; ++i) {
        auto space = wstring(
                (unsigned int) ((spacePerColumn - to_wstring(header[i]).length()) / 2.0),
                HISTOGRAM_SPACE
        );
        wcout << space << header[i] << space;
    }
    wcout << endl;
}