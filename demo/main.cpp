
#include "librosa/utils/files.h"
#include "librosa/feature/spectral.h"
#include "tool/print.h"
#include "librosa/filters.h"
#include "scipy/signal/windows/windows.h"
#include "numpy/core/function_base.h"
#include "numpy/lib/arraypad.h"
#include "numpy/fft/pocketfft.h"
#include "librosa/utils/utils.h"
#include "librosa/core/spectrum.h"
#include "librosa/core/convert.h"
#include "numpy/core/numeric.h"
#include "numpy/core/multiarray.h"
#include "scipy/fftpack/realtransforms.h"
#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) {
    std::string wav_fname(argv[1]);
    std::cout << "Wav path: " << wav_fname << std::endl;
    std::vector<float> audio = librosa::load(wav_fname);
    PrintFile("audio.txt", audio);
    auto start = std::chrono::system_clock::now();
    auto features = librosa::mfcc(audio, 16000, std::optional<std::vector<std::vector<float>>>(), 60);
    std::cout << features.size() << std::endl;
    std::cout << features[0].size() << std::endl;
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    PrintFile("mfcc.txt", features);
}
