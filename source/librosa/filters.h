
#pragma once

#include <optional>
#include <vector>

namespace librosa {

std::vector<std::vector<float>> mel(int sr, int n_fft, int n_mels = 128, float fmin = 0.f, std::optional<float> fmax = std::optional<float>(), bool htk = false, const std::string &norm = "slaney");

std::vector<float> get_window(const std::string &window, int Nx, bool fftbins = true);

}

