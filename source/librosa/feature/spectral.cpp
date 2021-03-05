
#include "spectral.h"
#include <algorithm>
#include <math.h>
#include <stdexcept>
#include "librosa/core/spectrum.h"
#include "scipy/fftpack/realtransforms.h"
#include "librosa/filters.h"
#include "numpy/core/multiarray.h"

namespace librosa {

std::vector<std::vector<float>> mfcc(const std::vector<float> &y, int sr,
                                     std::optional<std::vector<std::vector<float>>> S, int n_mfcc,
                                     int dct_type, const std::string &norm,
                                     int lifter) {
    if (!S) {
        S.emplace();
        std::vector<std::vector<float>> powers = melspectrogram(y, sr);
        S = power_to_db(powers);
    }

    std::vector<std::vector<float>> M(n_mfcc, std::vector<float>((*S)[0].size()));
    for (int i = 0; i < (*S)[0].size(); ++i) {
        std::vector<float> dct_input((*S).size());
        for (int j = 0; j < (*S).size(); ++j) {
            dct_input[j] = (*S)[j][i];
        }
        std::vector<float> dct_output = scipy::dct(dct_input, dct_type, std::optional<int>(), 0, norm);
        for (int j = 0; j < n_mfcc; ++j) {
            M[j][i] = dct_output[j];
        }
    }

    if (lifter > 0) {
        abort();
    } else if (lifter == 0) {
        return M;
    } else {
        throw std::invalid_argument("MFCC lifter must be a non-negative number");
    }
}

std::vector<std::vector<float>>
melspectrogram(const std::vector<float> &y, int sr,
               std::optional<std::vector<std::vector<float>>> S, int n_fft,
               int hop_length, std::optional<int> win_lenght,
               const std::string &window, bool center,
               const std::string &pad_mode, float power) {
    auto temp = _spectrogram(y, S, n_fft, hop_length, power, win_lenght, window, center, pad_mode);
    std::tie(S, n_fft) = temp;
    std::vector<std::vector<float>> mel_basis = librosa::mel(sr, n_fft);
    return numpy::dot(mel_basis, *S);
}

}

