#include <iostream>
#include "readers/WaveReader.h"
#include "terminal/Histogram.h"
#include <windows.h>
#include <conio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not found file in passed arguments");
        return -1;
    }

    WaveReader reader(argv[1]);
    double *hg;
    unsigned int second = 0;
    auto maxSeconds = (unsigned int) floor((double) reader.SamplesTotal / reader.metadata.SampleRate);

    using namespace std;
    wcout << fixed;
    auto render = [&] {
        wcout << flush;
        system("cls");

        hg = reader.GetFrequencyHistogram(second * reader.metadata.SampleRate);
        wcout << endl;
        wcout << "Frequency histogram at " << second << "s of " << maxSeconds << "s" << endl << endl;
        Terminal::printHistogram(reader.histogramHeader, hg, 7, 0.0, 1.0, 0.1);
        wcout << endl << endl << wstring(30, HISTOGRAM_FRAME_HORIZONTAL) << endl;
        wcout << "Detailed statistics:" << endl;
        wcout.precision(5);
        for (int i = 0; i < 7; ++i)
            wcout << reader.histogramHeader[i] << "Hz\t" << hg[i] << endl;
    };
    render();
    while (true) {
        if (kbhit()) {
            _getch();
            if (GetAsyncKeyState(VK_RIGHT)) {
                if ((int) second + 1 > maxSeconds)
                    second = maxSeconds;
                else {
                    ++second;
                    render();
                }
            } else if (GetAsyncKeyState(VK_LEFT)) {
                if ((int) second - 1 < 0)
                    second = 0;
                else {
                    --second;
                    render();
                }
            } else if (GetAsyncKeyState(0x51)) { // 0x51 is for Q-key
                break;
            }
        }
    }
    return 0;
}
