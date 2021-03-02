
#pragma once

#include <vector>
#include <string>

namespace numpy {

std::vector<float> pad(const std::vector<float> &array, int pad_width, const std::string &mode);

}

