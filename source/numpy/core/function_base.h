
#pragma once

#include <vector>

namespace numpy {

std::vector<float> linspace(float start, float stop, int num = 50, bool endpoint = true, bool retstep = false);

std::vector<float> diff(const std::vector<float> &a);

}

