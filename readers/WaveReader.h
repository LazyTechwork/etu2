#pragma once

#define MATH_PI 3.141593
#define MAX_FREQ 20000

#include <iostream>
#include <cstring>
#include <complex>
#include <vector>
#include <cmath>
#include <numeric>

struct FrequencyHistogram {
    int histogramHeader[7];
    double histogramValue[7];
};

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

typedef std::complex<double> coamp;

class WaveReader {
public:
    int *histogramHeader;
    WaveMetadata metadata{};
    short int *data;
    int SampleSize;
    int SamplesTotal;

    explicit WaveReader(const char *fileName);

    std::vector<coamp> GetComplexAmplitudes(unsigned int begin, unsigned int end = 0) const;

    double *GetFrequencyHistogram(int sampleOffset) const;
};
