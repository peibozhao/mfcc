
#pragma once

#include <vector>
#include <tuple>

namespace scipy {

inline std::tuple<int, bool> _extend(int M, bool sym) {
    return sym ? std::make_tuple(M, false) : std::make_tuple(M + 1, true);
}

inline std::vector<float> _truncate(const std::vector<float> &w, bool needed) {
    return needed ? std::vector<float>(w.begin(), w.end() - 1) : w;
}

std::vector<float> general_cosine(int M, const std::vector<float> &a, bool sym = true);

inline std::vector<float> general_hamming(int M, float alpha, bool sym = true) {
    return general_cosine(M, {alpha, 1.f - alpha}, sym);
}

inline std::vector<float> hann(int M, bool sym = true) {
    return general_hamming(M, 0.5, sym);
}

inline std::vector<float> get_window(const std::string &window, int Nx, bool fftbins = true) {
    bool sym = !fftbins;
    if (window == "hann") {
        return hann(Nx, sym);
    } else {
        abort();
    }
}

}

