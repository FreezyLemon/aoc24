// Needs C++23 for zip_view

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <ranges>

using std::ifstream;
using std::stringstream;

void die(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}


int main(int _argc, char *_argv[]) {
    ifstream infile("day1.txt");

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

        // std::cout << left_int << "|" << right_int << std::endl;
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    const auto zipped = std::ranges::zip_view(left, right);
    const auto diff_fn = [](const auto vals) { return std::abs(std::get<0>(vals) - std::get<1>(vals)); };
    const auto sum_fn = [](const int acc, const int diff) { return acc + diff; };
    const int sum = std::transform_reduce(zipped.begin(), zipped.end(), 0, sum_fn, diff_fn);

    std::cout << sum << std::endl;

    return 0;
}
