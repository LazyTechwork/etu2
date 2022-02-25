#include <iostream>
#include "readers/WaveReader.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not found file in passed arguments");
        return -1;
    }
    WaveReader reader(argv[1], true);
    reader.PrintSamples ();
    return 0;
}
