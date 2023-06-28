#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include "histogram.h"

void generate_numbers() {
    size_t number_count = rand() % 999 + 1;
    std::vector<double> numbers(number_count);

    std::ofstream out("input3.txt");
    out << number_count << "\n";

    for (auto& elem : numbers) {
        elem = rand() % 100;
        out << elem << " ";
    }

    out << "\n" << rand() % 9 + 1;
}

std::vector<size_t> make_histogram(std::vector<double> numbers, size_t bin_count) {
    auto min = *std::ranges::min_element(numbers);
    auto max = *std::ranges::max_element(numbers);

    double bin_size = (max - min) / bin_count;
    std::vector<size_t> bins(bin_count);

    std::ranges::for_each(std::as_const(numbers), [&](const auto& number) {
        auto lb = min, hb = min + bin_size;
        bool found = false;
        std::ranges::for_each(bins, [&](size_t& count) {
            if (number >= lb && number < hb && !found) {
                count++;
                found = true;
            }
            lb += bin_size;
            hb += bin_size;
            });
        if (!found) {
            bins[bin_count - 1]++;
        }
        });
    return bins;
}

void draw_histogram(std::vector<size_t> bins) {
    std::ranges::for_each(std::as_const(bins), [&](const auto& count) {
        auto max_row = *std::ranges::max_element(bins);
        size_t height = count;
        if (max_row > 76) {
            height = 76 * (double)count / max_row;
        }

        std::string str(height, '*');

        std::cout << std::setw(3) << count << "|" << str << "\n";
        });
}

void svg_begin(double width, double height) {
    std::cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    std::cout << "<svg ";
    std::cout << "width='" << width << "' ";
    std::cout << "height='" << height << "' ";
    std::cout << "viewBox='0 0 " << width << " " << height << "' ";
    std::cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, std::string text) {
    std::cout << "<text x='" << left << "' y='" << baseline << "'>" + text + "</text>";
}
void svg_end() {
    std::cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height,
    std::string stroke = "black", std::string fill = "black") {
    std::cout << "<rect x = '" << x << "' y = '" << y << "' width = '" << width << "' height = '" << height << "' stroke = '" 
        << stroke << "' fill = '" << fill << "'/>";
}

void show_histogram_svg(const std::vector<size_t>& bins, std::vector<std::string> colors) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    auto max = *std::ranges::max_element(bins);

    double top = 0;
    size_t color_index = 0;
    for (size_t bin : bins) {
        double bin_width = bin;
        if (max > 40) {
            bin_width = BLOCK_WIDTH * 40 * bin_width / max;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, colors[color_index], colors[color_index]);
        top += BIN_HEIGHT;
        color_index++;
    }
    svg_end();
}

bool check_color(std::string& color) {
    if (color.find('#') == 0 || !(color.find(' ') != std::string::npos)) {
        color.erase(0, 1);
        return true;
    }
    return false;
}

std::vector<std::string> input_colors(size_t colors_count) {
    std::vector<std::string> colors;
    std::string current_color;
    for (size_t i = 0; i < colors_count; i++) {
        std::cin >> current_color;
        if (check_color(current_color)) {
            colors.push_back(current_color);
        }
        else throw "Incorrect color";
    }
    return colors;
}

int main()
{
    size_t number_count;
    size_t bin_count;
    std::cin >> number_count;
    auto numbers = input_numbers(number_count);
    std::cin >> bin_count;

    auto bins = make_histogram(numbers, bin_count);
    auto colors = input_colors(bin_count);

    //draw_histogram(bins);
    show_histogram_svg(bins, colors);
}