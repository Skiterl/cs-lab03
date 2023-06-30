#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "histogram.h"
#include "histogram_svg.h"

#define CURL_STATICLIB
#include <curl/curl.h>

Input read_input(std::istream& in, bool prompt) {
    Input data;
    if(prompt)
        std::cerr << "Enter number count";

    size_t number_count;
    in >> number_count;
    if (prompt)
        std::cerr << "Enter numbers";
    data.numbers = input_numbers(in, number_count);
    
    if (prompt)
        std::cerr << "Enter bin count";
    in >> data.bin_count;

    return data;
}

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

std::vector<size_t> make_histogram(Input input) {
    auto min = *std::ranges::min_element(input.numbers);
    auto max = *std::ranges::max_element(input.numbers);

    double bin_size = (max - min) / input.bin_count;
    std::vector<size_t> bins(input.bin_count);

    std::ranges::for_each(std::as_const(input.numbers), [&](const auto& number) {
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
            bins[input.bin_count - 1]++;
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

Input download(const std::string& address) {
    std::stringstream buffer;

    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed" << "\n";
            exit(1);
        }
        curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}


int main(int argc, char* argv[])
{
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    }
    else {
        input = read_input(std::cin, true);
    }

    auto bins = make_histogram(input);
    auto colors = input_colors(input.bin_count);

    //draw_histogram(bins);
    show_histogram_svg(bins, colors);
}