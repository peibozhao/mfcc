
#include "pocketfft.h"

namespace numpy {

std::vector<std::complex<float>> rfft(const std::vector<float> &a, std::optional<int> n, int axis, const std::optional<std::string> &norm) {
    float inv_norm = 1.f;
    if (norm) {
        abort();
    }
    return _raw_fft(a, n, axis, true, true, inv_norm);
}

std::vector<std::complex<float>> _raw_fft(const std::vector<float> &a, std::optional<int> n, int axis, bool is_real, bool is_forward, float inv_norm) {
    if (!n) {
        n = a.size();
    }
    float fct = 1 / inv_norm;
    if (a.size() != n) {
        abort();
    }

    return execute(a, is_real, is_forward, fct);
}

}

