#include <cassert>
#include <ranges>
#include "../histogram_svg.h"

void test_positive() {
	double arr[3]{ 1, 2, 3 };
	double min = *std::ranges::min_element(arr);
	double max = *std::ranges::max_element(arr);
	assert(min == 1);
	assert(max == 3);
}

void test_negative() {
	double arr[3]{ -1, -2, -3 };
	double min = *std::ranges::min_element(arr);
	double max = *std::ranges::max_element(arr);
	assert(min == -3);
	assert(max == -1);
}

void test_equals() {
	double arr[3]{ 1, 1, 1 };
	double min = *std::ranges::min_element(arr);
	double max = *std::ranges::max_element(arr);
	assert(min == 1);
	assert(max == 1);
}

void test_one() {
	double arr[1]{ 1};
	double min = *std::ranges::min_element(arr);
	double max = *std::ranges::max_element(arr);
	assert(min == 1);
	assert(max == 1);
}

void test_check_color() {
	std::string color_white = "#FFF";
	std::string color_blue = "blue";
	std::string no_color = "no color";
	assert(check_color(color_blue));
	assert(check_color(color_white));
	assert(!check_color(no_color));
}


int main() {
	test_positive();
	test_negative();
	test_equals();
	test_one();
	test_check_color();
}