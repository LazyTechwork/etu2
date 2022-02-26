#include <iostream>
#include "readers/WaveReader.h"
#include "terminal/Histogram.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not found file in passed arguments");
        return -1;
    }

    WaveReader reader(argv[1]);
    double *hg;
    unsigned int second = 0;

    using namespace std;
    while (true) {
        hg = reader.GetFrequencyHistogram(second * reader.metadata.SampleRate);
        wcout << endl;
        wcout << "Frequency histogram at " << second << "s" << endl << endl;
        Terminal::printHistogram(reader.histogramHeader, hg, 7, 0.0, 1.0, 0.1);
        getchar();
        wcout << flush;
        system("cls");
        ++second;
    }
    return 0;
}
