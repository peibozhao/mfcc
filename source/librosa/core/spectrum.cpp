
#include "spectrum.h"
#include "librosa/filters.h"
#include "librosa/utils/utils.h"
#include "numpy/core/numeric.h"
#include "numpy/lib/arraypad.h"
#include "numpy/fft/pocketfft.h"
#include <algorithm>
#include <cmath>

namespace librosa {

std::vector<std::vector<float>> power_to_db(const std::vector<std::vector<float>> &S, float ref, float amin, std::optional<float> top_db) {
    if (amin <= 0) {
        throw std::invalid_argument("amin must be strictly positive");
    }
    const std::vector<std::vector<float>> &magnitude = S;
    float ref_value = std::abs(ref);

    std::vector<std::vector<float>> log_spec(magnitude.size(), std::vector<float>(magnitude[0].size()));
    for (int i = 0; i < log_spec.size(); ++i) {
        for (int j = 0; j < log_spec[0].size(); ++j) {
            log_spec[i][j] = 10.f * std::log10(std::max(amin, magnitude[i][j]));
            log_spec[i][j] -= 10.f * std::log10(std::max(amin, ref_value));
        }
    }

    if (top_db) {
        if (top_db < 0) {
            throw std::invalid_argument("top_db must be non-negative");
        }
        float log_spec_max = log_spec[0][0];
        for (int i = 0; i < log_spec.size(); ++i) {
            auto iter = std::max_element(log_spec[i].begin(), log_spec[i].end());
            log_spec_max = *iter > log_spec_max ? *iter : log_spec_max;
        }
        log_spec_max -= *top_db;

        std::for_each(
            log_spec.begin(), log_spec.end(), [log_spec_max](std::vector<float> &sub_log_spec) {
                std::for_each(sub_log_spec.begin(), sub_log_spec.end(),
                              [log_spec_max](float &num) { num = std::max(num, log_spec_max); });
            });
    }
    return log_spec;
}

std::tuple<std::vector<std::vector<float>>, int>
_spectrogram(const std::vector<float> &y, std::optional<std::vector<std::vector<float>>> S, int n_fft,
             int hop_length, int power, std::optional<int> win_lenght, const std::string &window,
             bool center, const std::string &pad_mode) {
    if (S) {
        n_fft = 2 * (S->size() - 1);
    } else {
        S.emplace();
        auto S_complex = stft(y, n_fft, hop_length, win_lenght, window, center, pad_mode);
        S->resize(S_complex.size());
        for (int i = 0; i < S_complex.size(); ++i) {
            (*S)[i].resize(S_complex[i].size());
            for (int j = 0; j < S_complex[i].size(); ++j) {
                (*S)[i][j] = std::pow(std::abs(S_complex[i][j]), power);
            }
        }
    }
    return std::make_tuple(*S, n_fft);
}

std::vector<std::vector<std::complex<float>>> stft(const std::vector<float> &y, int n_fft,
                                     std::optional<int> hop_length, std::optional<int> win_length,
                                     const std::string &window, bool center,
                                     const std::string &pad_mode) {
    std::vector<float> y_bak = y;
    if (!win_length) {
        win_length = n_fft;
    }

    if (!hop_length) {
        hop_length = *win_length / 4;
    }

    std::vector<float> fft_window = get_window(window, *win_length, true);

    // TODO
    // Pad window out to n_fft size

    if (center) {
        if (n_fft > y_bak.size()) {
            // Warning
        }
        y_bak = numpy::pad(y, n_fft / 2, pad_mode);
    } else if (n_fft > y_bak.size()) {
        abort();
    }

    std::vector<std::vector<float>> y_frames = librosa::frame(y_bak, n_fft, *hop_length);

    std::vector<std::vector<std::complex<float>>> stft_matrix(1 + n_fft / 2, std::vector<std::complex<float>>(y_frames[0].size()));

    for (int i = 0; i < stft_matrix[0].size(); ++i) {
        std::vector<float> y_frame(y_frames.size());
        for (int j = 0; j < y_frames.size(); ++j) {
            y_frame[j] = y_frames[j][i];
        }
        std::vector<float> rfft_input(fft_window.size());
        for (int k = 0; k < fft_window.size(); ++k) {
            rfft_input[k] = fft_window[k] * y_frame[k];
        }
        std::vector<std::complex<float>> stft_col = numpy::rfft(rfft_input);
        for (int j = 0; j < stft_matrix.size(); ++j) {
            stft_matrix[j][i] = stft_col[j];
        }
    }
    return std::move(stft_matrix);
}

} // namespace librosa
