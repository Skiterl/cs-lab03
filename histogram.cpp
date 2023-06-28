#include "histogram.h"

std::vector<double> input_numbers(size_t number_count) {
    std::vector<double> numbers(number_count);
    for (auto& elem : numbers) {
        std::cin >> elem;
    }
    return numbers;
}