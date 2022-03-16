#include "WaveReader.h"

WaveReader::WaveReader(const char *fileName) {
    histogramHeader = new int[7]{50, 100, 1000, 2000, 5000, 10000, 20000};
//        Opening file and reading metadata at the top of the binary
    FILE *waveFile = fopen(fileName, "rb");

    if (waveFile == nullptr) {
        std::wcout << "Cannot open file at " << fileName << std::endl;
        exit(-1);
    }

    fread(&metadata, sizeof(metadata), 1, waveFile);

//        Seeking for data chunk
    WaveChunk chunk{};
    while (true) {
        fread(&chunk, sizeof(chunk), 1, waveFile);
        if (*(unsigned int *) &chunk.DATA == 0x61746164) // 0x61746164 is for "data" in BIG-ENDIAN
            break;
        fseek(waveFile, chunk.size, SEEK_CUR);
    }

//        Calculating sample size and total count of samples
    SampleSize = metadata.BitsPerSample / 8;
    SamplesTotal = chunk.size * 8 / metadata.BitsPerSample;

//        Acquiring space for data store and emptying it
    data = new short int[SamplesTotal];
//    Amplitudes = new unsigned short int[SamplesTotal];
    memset(data, 0, sizeof(short int) * SamplesTotal);

//        Reading data
    for (int i = 0; i < SamplesTotal; i++)
        fread(&data[i], SampleSize, 1, waveFile);

//        Closing file
    fclose(waveFile);
}

std::vector<coamp> WaveReader::GetComplexAmplitudes(unsigned int begin, unsigned int end) const {
    std::vector<coamp> ComplexAmplitudes;
    for (unsigned int k = 0, N = end - begin; k < MAX_FREQ + 1; ++k) {
        auto amplitude = coamp(0.0f, 0.0f);
        for (int n = 0; n < N; ++n) {
            double X = 2 * MATH_PI * k * n / N;
            amplitude += coamp(data[begin + n], 0) * coamp(cos(X), sin(X));
        }
        amplitude /= N;
        ComplexAmplitudes.push_back(amplitude);
    }
    return ComplexAmplitudes;
}

double *WaveReader::GetFrequencyHistogram(int sampleOffset) const {
    const int dataSize = SamplesTotal;
    const auto sampleRate = metadata.SampleRate;
    int sampleTo = sampleOffset +
                   (sampleOffset + sampleRate <= dataSize ? sampleRate : dataSize - sampleOffset);

    auto notFreqsButOk = data;


    unsigned int histogramData[]{0, 0, 0, 0, 0, 0, 0};

    unsigned short int val;
    for (int i = sampleOffset; i < sampleTo; ++i) {
        val = notFreqsButOk[i];
        for (int hi = 0, from, to; hi < 7; ++hi) {
            from = hi != 0 ? histogramHeader[hi - 1] : 0;
            to = histogramHeader[hi] + histogramHeader[hi] / 10;
            if (from <= val && val < to) {
                histogramData[hi]++;
                break;
            }
        }
    }

    const double histogramWeight = std::accumulate(
            std::begin(histogramData), std::end(histogramData), 0.0);

    auto *histogramValues = new double[7];
    for (int i = 0; i < 7; ++i)
        histogramValues[i] = histogramData[i] / histogramWeight;


    return histogramValues;
}
