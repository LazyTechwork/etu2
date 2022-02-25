#include "WaveReader.h"

WaveReader::WaveReader(const char *fileName, bool debug) {
    //        Opening file and reading metadata at the top of the binary
    FILE *waveFile = fopen(fileName, "rb");
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
    Amplitudes = new unsigned short int[SamplesTotal];
    memset(data, 0, sizeof(short int) * SamplesTotal);

//        Reading data
    for (int i = 0; i < SamplesTotal; i++)
        fread(&data[i], SampleSize, 1, waveFile);

//        Closing file
    fclose(waveFile);

//        If debug argument passed - printing debug information
    if (debug) {
        printf("File: %s\n", fileName);
        printf("File Type: %s\n", metadata.RIFF);
        printf("File Size: %ld\n", metadata.ChunkSize);
        printf("WAV Marker: %s\n", metadata.WAVE);
        printf("Format Name: %s\n", metadata.fmt);
        printf("Format Length: %ld\n", metadata.Subchunk1Size);
        printf("Format Type: %hd\n", metadata.AudioFormat);
        printf("Number of Channels: %hd\n", metadata.Channels);
        printf("Sample Rate: %ld\n", metadata.SampleRate);
        printf("Sample Rate * Bits/Sample * Channels / 8: %ld\n", metadata.ByteRate);
        printf("Bits per Sample * Channels / 8: %hd\n", metadata.BlockAlign);
        printf("Bits per Sample: %hd\n", metadata.BitsPerSample);
        printf("Samples count: %i\n", SamplesTotal);
    }
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
