
#include "convert.h"
#include <cmath>
#include "numpy/core/function_base.h"

#include <iostream>

namespace librosa {

std::vector<float> fft_frequencies(int sr, int n_fft) {
    return numpy::linspace(0, float(sr) / 2, 1 + n_fft / 2);
}

std::vector<float> mel_frequencies(int n_mels, float fmin, float fmax, bool htk) {
    float min_mel = hz_to_mel(fmin, htk);
    float max_mel = hz_to_mel(fmax, htk);
    std::vector<float> mels = numpy::linspace(min_mel, max_mel, n_mels);
    std::vector<float> ret;
    for (float mel : mels) {
        ret.push_back(mel_to_hz(mel, htk));
    }
    return ret;
}

float hz_to_mel(float frequencies, bool htk) {
    if (htk) {
        return 2595.f * std::log10(1.f + frequencies / 700.f);
    }

    float f_min = 0.f;
    float f_sp = 200.f / 3;
    float mels = (frequencies - f_min) / f_sp;
    float min_log_hz = 1000.f;
    float min_log_mel = (min_log_hz - f_min) / f_sp;
    float logstep = std::log(6.4) / 27.f;

    if (frequencies >= min_log_hz) {
        mels = min_log_mel + std::log(frequencies / min_log_hz) / logstep;
    }
    return mels;
}

float mel_to_hz(float mel, bool htk) {
    if (htk) {
        return 700.f * (std::pow(10.f, mel / 2595.f) - 1.f);
    }

    float f_min = 0.f;
    float f_sp = 200.f / 3;
    float freqs = f_min + f_sp * mel;
    float min_log_hz = 1000.f;
    float min_log_mel = (min_log_hz - f_min) / f_sp;
    float logstep = std::log(6.4) / 27.f;

    if (mel >= min_log_mel) {
        freqs = min_log_hz * std::exp(logstep * (mel - min_log_mel));
    }
    return freqs;
}

}

