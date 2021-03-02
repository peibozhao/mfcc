
#pragma once

#include <vector>
#include <optional>
#include <string>

namespace numpy {

std::vector<float> ones(int dim1);
std::vector<std::vector<float>> ones(int dim1, int dim2);

std::vector<float> zeros(int dim1);
std::vector<std::vector<float>> zeros(int dim1, int dim2);

}

