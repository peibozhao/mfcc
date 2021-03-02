
#include "arraypad.h"

namespace numpy {

std::vector<float> pad(const std::vector<float> &array, int pad_width, const std::string &mode) {
    std::vector<float> ret(array.size() + pad_width * 2);
    if (mode == "reflect") {
        std::copy(array.begin(), array.end(), ret.begin() + pad_width);
        for (int i = 0; i < pad_width; ++i) {
            ret[pad_width - i - 1] = ret[pad_width + i + 1];
            ret[pad_width + array.size() + i] = ret[pad_width + array.size() - i - 2];
        }
    } else {
        abort();
    }
    return ret;
}

}

