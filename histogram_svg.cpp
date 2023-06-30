#include "histogram_svg.h"
#include "histogram.h"

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

void show_histogram_svg(const std::vector<size_t>& bins, Input input) {
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
        if (max > 35) {
            bin_width = BLOCK_WIDTH * 35 * bin_width / max;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, input.colors[color_index], input.colors[color_index]);
        top += BIN_HEIGHT;
        color_index++;
    }
    svg_end();
}

bool check_color(std::string& color) {
    if (color.find('#') == 0 || !(color.find(' ') != std::string::npos)) {
        return true;
    }
    return false;
}