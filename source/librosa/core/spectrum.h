
#pragma once

#include <vector>
#include <tuple>
#include <optional>
#include <complex>

namespace librosa {

std::vector<std::vector<float>> power_to_db(const std::vector<std::vector<float>> &S, float ref = 1.f, float amin = 1e-10, std::optional<float> top_db = 80.f);

std::tuple<std::vector<std::vector<float>>, int> _spectrogram(const std::vector<float> &y = {},  std::optional<std::vector<std::vector<float>>> S = std::optional<std::vector<std::vector<float>>>(), int n_fft = 2048, int hop_length = 512, int power = 1, std::optional<int> win_lenght = std::optional<int>(), const std::string &window = "hann", bool center = true, const std::string &pad_mode = "reflect");

std::vector<std::vector<std::complex<float>>> stft(const std::vector<float> &y, int n_fft = 2048, std::optional<int> hop_length = std::optional<int>(), std::optional<int> win_length = std::optional<int>(), const std::string &window = "hann", bool center = true, const std::string &pad_mode = "reflect");

}

