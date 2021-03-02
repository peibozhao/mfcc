
#pragma once

#include <ostream>
#include <fstream>
#include <vector>

#include <iostream>


template <typename T>
std::ostream & operator<< (std::ostream &os, const std::vector<T> &data) {
    os.precision(5);
    for (auto &sub_data : data) {
        os << sub_data << " ";
    }
    os << std::endl;
    return os;
}

template <typename T>
void PrintFile(const std::string &fname, const T &data) {
    std::ofstream ofs(fname);
    ofs << data;
}

