#include "histogram.h"

std::vector<double> input_numbers(std::istream& in, size_t number_count) {
    std::vector<double> numbers(number_count);
    for (auto& elem : numbers) {
        in >> elem;
    }
    return numbers;
}