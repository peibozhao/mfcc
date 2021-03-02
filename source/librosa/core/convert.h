
#pragma once

#include <vector>

namespace librosa {

std::vector<float> fft_frequencies(int sr = 22050, int n_fft = 2048);

std::vector<float> mel_frequencies(int n_mels = 128, float fmin = 0.f, float fmax = 11025.f, bool htk = false);

float hz_to_mel(float frequencies, bool htk = false);

float mel_to_hz(float mel, bool htk = false);

}


