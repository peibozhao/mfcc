
#pragma once

#include <string>
#include <optional>

inline int _normalization(const std::optional<std::string> &norm, bool forward) {
    int inorm = 0;
    if (norm == "backward") {
        inorm = 0;
    } else if (norm == "ortho") {
        inorm = 1;
    } else if (norm == "forward") {
        inorm = 2;
    }
    return forward ? inorm : 2 - inorm;
}

