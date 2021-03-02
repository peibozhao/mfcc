
#include "function_base.h"

namespace numpy {

// TODO
std::vector<float> linspace(float start, float stop, int num, bool endpoint, bool retstep) {
    std::vector<float> ret(num);
    float offset = (stop - start) / (num - 1);
    for (int i = 0; i < num; ++i) {
        ret[i] = start + i * offset;
    }
    ret[ret.size() - 1] = stop;
    return ret;
}

std::vector<float> diff(const std::vector<float> &a) {
    if (a.empty()) {
        return {};
    }
    std::vector<float> ret;
    for (auto iter = a.begin() + 1; iter != a.end(); ++iter) {
        ret.push_back(*iter - *(iter - 1));
    }
    return ret;
}

}

