
#pragma once

#include <vector>

namespace librosa {

std::vector<std::vector<float>> frame(const std::vector<float> &x, int frame_length, int hop_length, int axis = -1);

}

