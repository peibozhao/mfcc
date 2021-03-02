
#include "multiarray.h"
#include <iostream>

namespace numpy {

std::vector<std::vector<float>> dot(const std::vector<std::vector<float>> &a, const std::vector<std::vector<float>> &b) {
    std::vector<std::vector<float>> ret(a.size(), std::vector<float>(b[0].size(), 0.f));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < a[i].size(); ++k) {
                ret[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ret;
}

}

