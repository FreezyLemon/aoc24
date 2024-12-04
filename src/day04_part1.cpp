#include "util.h"

#include <iostream>
#include <string>
#include <tuple>

constexpr std::tuple<char, char, char, char> xmas() {
    return std::make_tuple('X', 'M', 'A', 'S');
}

constexpr std::tuple<char, char, char, char> samx() {
    return std::make_tuple('S', 'A', 'M', 'X');
}

// X
//  M
//   A
//    S
bool is_xmas_diag(const std::string_view str, int length) {
    // don't wrap around line endings
    if (str.find('\n') < 4) {
        return false;
    }

    // don't overshoot str
    int required_len = 3 + 3 * length;
    if (str.length() < required_len) {
        return false;
    }

    const auto found = std::make_tuple(
        str[0],
        str[length + 1],
        str[2 * length + 2],
        str[3 * length + 3]
    );

    return found == xmas() || found == samx();
}

//    X
//   M
//  A
// S
bool is_xmas_reverse_diag(const std::string_view str, int length) {
    // don't wrap around line endings
    if (str.find('\n') < 4) {
        return false;
    }

    // don't overshoot str
    int required_len = 3 + 3 * length;
    if (str.length() < required_len) {
        return false;
    }

    const auto found = std::make_tuple(
        str[3],
        str[2 + length],
        str[1 + 2 * length],
        str[3 * length]
    );

    return found == xmas() || found == samx();
}

// X
// M
// A
// S
bool is_xmas_vertical(const std::string_view str, int length) {
    // don't overshoot str
    int required_len = 3 * length;
    if (str.length() < required_len) {
        return false;
    }

    const auto found = std::make_tuple(
        str[0],
        str[length],
        str[2 * length],
        str[3 * length]
    );

    return found == xmas() || found == samx();
}

// XMAS
bool is_xmas_horizontal(const std::string_view str, int length) {
    // don't wrap around line endings
    if (str.length() < 4 || str.find('\n') < 4) {
        return false;
    }

    const auto found = std::make_tuple(str[0], str[1], str[2], str[3]);

    return found == xmas() || found == samx();
}

int main(int argc, char *argv[]) {
    auto infile = open_input(argc, argv);
    const std::string content(
        (std::istreambuf_iterator<char>(infile)),
        (std::istreambuf_iterator<char>())
    );

    const std::string_view sv(content);
    // assumption: line length is constant
    const int width = sv.find('\n');
    const int height = sv.length() / width;
    std::cout << width << "x" << height << std::endl;

    int sum = 0;
    for (int i = 0; i < sv.length(); i++) {
        const auto substr = sv.substr(i);
        // width does not include \n, so we need 1 + width
        sum += is_xmas_diag(substr, 1 + width);
        sum += is_xmas_reverse_diag(substr, 1 + width);
        sum += is_xmas_horizontal(substr, 1 + width);
        sum += is_xmas_vertical(substr, 1 + width);
    }

    std::cout << sum << std::endl;

    return 0;
}
