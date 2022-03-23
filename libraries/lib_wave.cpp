#include <iostream>
#include <conio.h>

#include "../readers/WaveReader.h"
#include "../terminal/Histogram.h"
#include "../terminal/Keyboard.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Pass filepath as first argument");
        return -1;
    }

    WaveReader reader(argv[1]);
    double *hg;
    unsigned int second = 0;
    auto maxSeconds = (unsigned int) floor((double) reader.SamplesTotal / reader.metadata.SampleRate);

    std::wcout << std::fixed;

    auto render = [&] {
        using namespace std;
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
        wcout << endl << wstring(30, HISTOGRAM_FRAME_HORIZONTAL) << endl;
        wcout << "Use left and right arrow keys to move over wav-file" << endl << "Press 'q' to exit" << endl;
    };

    render();
    while (true) {
        switch (_getch()) {
            case 'q':
                break;
            case ARROW_PREFIX:
                switch (_getch()) {
                    case ARROW_RIGHT:
                        if ((int) second + 1 > maxSeconds)
                            second = maxSeconds;
                        else {
                            ++second;
                            render();
                        }
                        break;
                    case ARROW_LEFT:
                        if ((int) second - 1 < 0)
                            second = 0;
                        else {
                            --second;
                            render();
                        }
                        break;
                }
                continue;
            default:
                continue;
        }
        break;
    }
    return 0;
}
