#ifndef HISTOGRAM_SVG_H_INCLUDED
#define HISTOGRAM_SVG_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>

using namespace std;

bool check_color(std::string& color) {
    if (color.find('#') == 0 || !(color.find(' ') != std::string::npos)) {
        return true;
    }
    return false;
}
void svg_begin(double width, double height);
void svg_text(double left, double baseline, std::string text);
void svg_end();
void svg_rect(double x, double y, double width, double height,
    std::string stroke, std::string fill);
void show_histogram_svg(const std::vector<size_t>& bins, std::vector<std::string> colors);
#endif