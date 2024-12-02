#include "util.h"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <iostream>
#include <ostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using std::operator""sv;

int parse(std::ranges::subrange<const char*> x) {
    int i;
    auto result = std::from_chars(x.data(), x.data() + x.size(), i);
    if (result.ec == std::errc::invalid_argument) {
        die("Could not convert");
    }

    return i;
}

int diff(const std::tuple<int, int> vals) {
    return std::get<0>(vals) - std::get<1>(vals);
}

bool check_levels(const std::vector<int> levels) {
    const auto diffs =
        levels |
        std::views::adjacent<2> |
        std::views::transform(diff) |
        std::ranges::to<std::vector<int>>();

    if (diffs.empty()) {
        die("need at least two levels per reports");
    }

    const bool negative = diffs[0] < 0;
    const bool all_diffs_valid = std::all_of(
        diffs.cbegin(),
        diffs.cend(),
        [negative](const int diff) {
            const int diff_abs = std::abs(diff);
            if (diff_abs < 1 || diff_abs > 3) {
                return false;
            }

            return (diff < 0) == negative;
        }
    );

    return all_diffs_valid;
}

int main(int argc, char *argv[]) {
    auto infile = open_input(argc, argv);

    std::string line;
    int safe_reports = 0;

    while (std::getline(infile, line)) {
        const auto levels =
            std::string_view(line) |
            std::views::split(" "sv) |
            std::views::transform(parse) |
            std::ranges::to<std::vector<int>>();

        const auto possible_dampeners =
            std::views::iota(0ul, levels.size()) |
            std::views::transform([levels](const unsigned long i) {
                auto subvec = levels;
                subvec.erase(subvec.begin() + i);
                return subvec;
            }) |
            std::ranges::to<std::vector<std::vector<int>>>();

        const bool any_safe_report = std::any_of(
            possible_dampeners.begin(),
            possible_dampeners.end(),
            check_levels
        );

        if (any_safe_report) {
            safe_reports++;
        }
    }

    std::cout << safe_reports << std::endl;

    return 0;
}
