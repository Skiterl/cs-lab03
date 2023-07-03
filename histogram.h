#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
#include <iostream>

struct Input {
    std::vector<double> numbers;
    size_t bin_count;
    std::vector<std::string> colors;
    double time_to_connect;
};

std::vector<double> input_numbers(std::istream&, size_t);

#endif