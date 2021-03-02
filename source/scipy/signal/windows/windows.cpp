
#include "windows.h"
#include <algorithm>
#include <math.h>
#include "numpy/core/function_base.h"
#include "numpy/init.h"
#include "numpy/core/numeric.h"

namespace scipy {

std::vector<float> general_cosine(int M, const std::vector<float> &a, bool sym) {
    std::tuple<int, bool> temp = _extend(M, sym);
    bool needs_trunc;
    std::tie(M, needs_trunc) = temp;

    std::vector<float> fac = numpy::linspace(-pi, pi, M);
    std::vector<float> w = numpy::zeros(M);
    for (int k = 0; k < a.size(); ++k) {
        for (int i = 0; i < w.size(); ++i) {
            w[i] += a[k] * std::cos(k * fac[i]);
        }
    }
    return _truncate(w, needs_trunc);
}

}
