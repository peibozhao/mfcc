
#include "numeric.h"

namespace numpy {

std::vector<float> ones(int dim1) {
    return std::vector<float>(dim1, 1);
}

std::vector<std::vector<float>> ones(int dim1, int dim2) {
    return std::vector<std::vector<float>>(dim1, std::vector<float>(dim2, 1.f));
}

std::vector<float> zeros(int dim1) {
    return std::vector<float>(dim1, 0);
}

std::vector<std::vector<float>> zeros(int dim1, int dim2) {
    return std::vector<std::vector<float>>(dim1, std::vector<float>(dim2, 0.f));
}

}

