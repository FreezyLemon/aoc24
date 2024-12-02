#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <system_error>
#include <vector>
#include <ranges>

#include "util.h"

using std::operator""sv;
using std::ifstream;
using std::stringstream;

int parse(std::ranges::subrange<const char*> piece) {
    int i;
    const auto result = std::from_chars(piece.data(), piece.data() + piece.size(), i);
    if (result.ec == std::errc::invalid_argument) {
        die("parsing failure");
    }

    return i;
}

int main(int argc, char *argv[]) {
    auto infile = open_input(argc, argv);

    std::string line;
    std::vector<int> left, right;
    while (std::getline(infile, line)) {
        const auto numbers =
            std::string_view(line) |
            std::views::split("   "sv) |
            std::views::transform(parse) |
            std::ranges::to<std::vector<int>>();

        if (numbers.size() != 2) {
            die("not exactly 2 numbers per line");
        }

        left.push_back(numbers[0]);
        right.push_back(numbers[1]);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    const auto diff_fn = [](const int l, const int r) { return std::abs(l - r); };
    const int sum = std::transform_reduce(left.begin(), left.end(), right.begin(), 0, std::plus(), diff_fn);

    std::cout << sum << std::endl;

    return 0;
}
