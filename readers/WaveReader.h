#ifndef MATH_PI
#define MATH_PI 3.141592
#endif

#ifndef ETU2_WAVEREADER_H
#define ETU2_WAVEREADER_H

#include <iostream>
#include <cstring>
#include <complex>
#include <vector>
#include <cmath>


struct WaveMetadata {
    char RIFF[4];                  // RIFF Header
    unsigned long ChunkSize;       // RIFF Chunk Size
    char WAVE[4];                  // WAVE Header
    char fmt[4];                   // FMT Metadata
    unsigned long Subchunk1Size;   // Size of the fmt chunk
    unsigned short AudioFormat;    // Audio format
    unsigned short Channels;       // Number of channels
    unsigned long SampleRate;      // Sampling Frequency
    unsigned long ByteRate;        // Bytes per second
    unsigned short BlockAlign;     // 2=16-bit mono, 4=16-bit stereo
    unsigned short BitsPerSample;  // Number of bits per sample
};

struct WaveChunk {
    char DATA[4];       // DATA Header
    unsigned long size; // Chunk data size
};

class WaveReader {
    WaveMetadata metadata{};
    short int *data;
    int SampleSize;
    int SamplesTotal;

public:
    explicit WaveReader(const char *fileName, bool debug = false);

    void PrintSamples();
};


#endif //ETU2_WAVEREADER_H
