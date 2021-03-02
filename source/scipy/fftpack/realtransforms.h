
#pragma once

#include <vector>
#include <optional>

namespace scipy {

std::vector<float> dct(const std::vector<float> &x, int type = 2, std::optional<int> n = std::optional<int>(), int axis = -1, const std::optional<std::string> &norm = std::optional<std::string>(), bool overwrite_x = false);

}

