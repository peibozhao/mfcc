
#pragma once

#include <optional>
#include <tuple>
#include <vector>

namespace librosa {

std::vector<std::vector<float>> mfcc(const std::vector<float> &y, int sr = 22050,
                                     std::optional<std::vector<std::vector<float>>> S = std::optional<std::vector<std::vector<float>>>(), int n_mfcc = 20,
                                     int dct_type = 2, const std::string &norm = "ortho",
                                     int lifter = 0);

std::vector<std::vector<float>>
melspectrogram(const std::vector<float> &y, int sr = 22050,
               std::optional<std::vector<std::vector<float>>> S = std::optional<std::vector<std::vector<float>>>(), int n_fft = 2048,
               int hop_length = 512, std::optional<int> win_lenght = std::optional<int>(),
               const std::string &window = "hann", bool center = true,
               const std::string &pad_mode = "reflect", float power = 2.f);

std::vector<float, float> stft(const std::vector<float> &y, int n_fft = 2048,
                               std::optional<int> hop_length = std::optional<int>(),
                               std::optional<int> win_length = std::optional<int>(),
                               const std::string &window = "hann", bool center = true,
                               std::optional<int> dtype = std::optional<int>(),
                               const std::string &pad_mode = "reflect");

}

