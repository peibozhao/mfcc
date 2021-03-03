
#include "librosa/core/convert.h"
#include "librosa/core/spectrum.h"
#include "librosa/feature/spectral.h"
#include "librosa/filters.h"
#include "librosa/utils/files.h"
#include "librosa/utils/utils.h"
#include "numpy/core/function_base.h"
#include "numpy/core/multiarray.h"
#include "numpy/core/numeric.h"
#include "numpy/fft/pocketfft.h"
#include "numpy/lib/arraypad.h"
#include "scipy/fftpack/realtransforms.h"
#include "scipy/signal/windows/windows.h"
#include "tool/print.h"
#include <chrono>
#include <iostream>

void Usage(const std::string &cmd) { std::cout << "Usage: " << cmd << " wav_path" << std::endl; }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Usage(argv[0]);
        return -1;
    }
    std::string wav_fname(argv[1]);
    std::cout << "Wav path: " << wav_fname << std::endl;
    std::vector<float> audio = librosa::load(wav_fname);
    PrintFile("audio.txt", audio);
    auto start = std::chrono::system_clock::now();
    auto features =
        librosa::mfcc(audio, 16000, std::optional<std::vector<std::vector<float>>>(), 60);
    auto end = std::chrono::system_clock::now();
    std::cout << "Cost: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms"
              << std::endl;
    PrintFile("mfcc.txt", features);
    std::cout << "Mfcc path: "
              << "mfcc.txt" << std::endl;
}
