// Needs C++23 for zip_view

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "util.h"

using std::ifstream;
using std::stringstream;

int main(int _argc, char *_argv[]) {
    ifstream infile("day01.txt");

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

    // almost definitely optimizable, idc for now
    const auto score_fn = [right](const int l) { return l * std::count(right.cbegin(), right.cend(), l); };
    const int score = std::transform_reduce(left.begin(), left.end(), 0, std::plus(), score_fn);

    std::cout << score << std::endl;

    return 0;
}
