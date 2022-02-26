#include <iostream>
#include "readers/WaveReader.h"
#include "terminal/Histogram.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not found file in passed arguments");
        return -1;
    }

    WaveReader reader(argv[1]);
    double *hg = reader.GetFrequencyHistogram(0);

    Terminal::printHistogram(reader.histogramHeader, hg, 7, 0.0, 1.0, 0.1);

    /*for (int i = 128; i < 256; ++i) {
        printf("%d\t%c\n", i, i);
    }
    printf("\n");*/
    getchar();
    return 0;
}
