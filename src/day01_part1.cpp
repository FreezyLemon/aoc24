#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "util.h"

using std::ifstream;
using std::stringstream;

int main(int argc, char *argv[]) {
    auto infile = open_input(argc, argv);

    std::string line;
    std::vector<int> left, right;
    while (std::getline(infile, line)) {
        const size_t first_space_idx = line.find(' ');
        if (first_space_idx == std::string::npos) {
            die("no space in line");
        }

        const auto left_str = line.substr(0, first_space_idx);
        // always 3 spaces
        const auto right_str = line.substr(first_space_idx + 3);

        const int left_int = std::stoi(left_str);
        const int right_int = std::stoi(right_str);

        left.push_back(left_int);
        right.push_back(right_int);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    const auto diff_fn = [](const int l, const int r) { return std::abs(l - r); };
    const int sum = std::transform_reduce(left.begin(), left.end(), right.begin(), 0, std::plus(), diff_fn);

    std::cout << sum << std::endl;

    return 0;
}
