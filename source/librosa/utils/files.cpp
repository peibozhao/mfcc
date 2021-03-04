
#include "files.h"
#include <fstream>
#include <algorithm>

namespace librosa {

// TODO
struct wavHeader {
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Stereo
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
};

std::vector<float> load(const std::string &fname) {
    std::ifstream ifs(fname, std::ios::binary);
    wavHeader wav_header;
    ifs.read((char *)&wav_header, sizeof(wav_header));
    if (std::string((char *)wav_header.Subchunk2ID, 4) != std::string("data")) {
        abort();
    }
    int sample_count = wav_header.Subchunk2Size / 2;
    std::vector<short> simples(sample_count);
    ifs.read((char *)simples.data(), sizeof(short) * sample_count);
    std::vector<float> ret;
    for (int i = 0; i < sample_count; ++i) {
        ret.push_back(simples[i] / 32768.f);
    }
    return ret;
}

}

