
#include "filters.h"
#include <algorithm>
#include "numpy/core/numeric.h"
#include "scipy/signal/windows/windows.h"
#include "librosa/core/convert.h"
#include "numpy/core/function_base.h"

namespace librosa {

std::vector<std::vector<float>> mel(int sr, int n_fft, int n_mels, float fmin, std::optional<float> fmax, bool htk, const std::string &norm) {
    if (!fmax) {
        fmax = float(sr) / 2;
    }
    std::vector<std::vector<float>> weights = numpy::zeros(n_mels, int(1 + n_fft / 2));
    std::vector<float> fftfreqs = librosa::fft_frequencies(sr, n_fft);
    std::vector<float> mel_f = librosa::mel_frequencies(n_mels + 2, fmin, *fmax, htk);
    std::vector<float> fdiff = numpy::diff(mel_f);

    std::vector<std::vector<float>> ramps(mel_f.size(), std::vector<float>(fftfreqs.size(), 0.f));
    for (int i = 0; i < mel_f.size(); ++i) {
        for (int j = 0; j < fftfreqs.size(); ++j) {
            ramps[i][j] = mel_f[i] - fftfreqs[j];
        }
    }

    for (int i = 0; i < n_mels; ++i) {
        std::vector<float> lower(ramps[i].size());
        std::vector<float> upper(ramps[i].size());
        for (int j = 0; j < ramps[i].size(); ++j) {
            lower[j] = -ramps[i][j] / fdiff[i];
            upper[j] = ramps[i + 2][j] / fdiff[i + 1];
            weights[i][j] = std::max(0.f, std::min(lower[j], upper[j]));
        }
    }

    if (norm == "slaney") {
        std::vector<float> enorm(n_mels);
        for (int i = 0; i < enorm.size(); ++i) {
            enorm[i] = 2.f / (mel_f[2 + i] - mel_f[i]);
        }
        for (int i = 0; i < weights.size(); ++i) {
            for (int j = 0; j < weights[0].size(); ++j) {
                weights[i][j] *= enorm[i];
            }
        }
    } else {
        abort();
    }
    return weights;
}

std::vector<float> get_window(const std::string &window, int Nx, bool fftbins) {
    return scipy::get_window(window, Nx, fftbins);
}

}

