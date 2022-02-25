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
    for (int i = 0; i < SamplesTotal; i++) {
        fread(&data[i], SampleSize, 1, waveFile);
        Amplitudes[i] = data[i] + SHRT_MAX + 1;
    }

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
        printf("Bits per Sample * Channels / 8.1: %hd\n", metadata.BlockAlign);
        printf("Bits per Sample: %hd\n", metadata.BitsPerSample);
        printf("Samples count: %i\n", SamplesTotal);
    }
}

void WaveReader::PrintSamples() {
    for (int i = 0; i < SamplesTotal; ++i)
        printf("%d ", Amplitudes[i]);
}
