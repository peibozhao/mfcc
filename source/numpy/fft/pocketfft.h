#pragma once

extern "C" {
#include "_pocketfft.h"
}

#include <vector>
#include <string>
#include <optional>
#include <complex>

namespace numpy {

std::vector<std::complex<float>> rfft(const std::vector<float> &a, std::optional<int> n = std::optional<int>(), int axis = -1, const std::optional<std::string> &norm = std::optional<std::string>());

std::vector<std::complex<float>> _raw_fft(const std::vector<float> &a, std::optional<int> n, int axis, bool is_real, bool is_forward, float inv_norm);

/* ------------------------------------------- */

inline std::vector<std::complex<float>> execute_real_forward(const std::vector<float> &a1, float fct) {
    float *ret_ptr;
    int retsize;
    if (::execute_real_forward(a1.data(), a1.size(), fct, &ret_ptr, &retsize) != 0) {
        return {};
    }
    std::vector<std::complex<float>> ret;
    for (int i = 0; i < retsize; i += 2) {
        ret.emplace_back(ret_ptr[i], ret_ptr[i + 1]);
    }
    free(ret_ptr);
    return ret;
}

inline std::vector<std::complex<float>> execute_real(const std::vector<float> &a1, bool is_forward, float fct) {
    if (is_forward) {
        return execute_real_forward(a1, fct);
    } else {
        abort();
    }
}

inline std::vector<std::complex<float>> execute(const std::vector<float> &a1, bool is_real, bool is_forward, float fct) {
    if (is_real) {
        return execute_real(a1, is_forward, fct);
    } else {
        abort();
    }
}

}

