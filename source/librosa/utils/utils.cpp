
#include "utils.h"
#include <iostream>

namespace librosa {

std::vector<std::vector<float>> frame(const std::vector<float> &x, int frame_length, int hop_length, int axis) {
    int n_frames = 1 + (x.size() - frame_length) / hop_length;
    std::vector<std::vector<float>> ret(frame_length, std::vector<float>(n_frames, 0.f));
    // TODO Order, cache
    for (int i = 0; i < n_frames; ++i) {
        for (int j = 0; j < frame_length; ++j) {
            ret[j][i] = x[i * hop_length + j];
        }
    }
    return ret;
}

}
