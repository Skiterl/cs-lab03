#include "../histogram.h"

#include <cassert>
#include <ranges>

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

int main() {
	test_positive();
}