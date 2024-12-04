#include "util.h"

#include <iostream>
#include <string>
#include <tuple>

constexpr std::tuple<char, char, char> mas() {
    return std::make_tuple('M', 'A', 'S');
}

constexpr std::tuple<char, char, char> sam() {
    return std::make_tuple('S', 'A', 'M');
}

// M S
//  A 
// M S
bool is_x_mas(const std::string_view str, int length) {
    // don't wrap around line endings
    if (str.find('\n') < 3) {
        return false;
    }

    // don't overshoot str
    int required_len = 2 + 2 * length;
    if (str.length() < required_len) {
        return false;
    }

    const auto diag = std::make_tuple(str[0], str[length + 1], str[2 * length + 2]);
    const auto rev_diag = std::make_tuple(str[2], str[length + 1], str[2 * length]);

    return (diag == sam() || diag == mas()) && (rev_diag == sam() || rev_diag == mas());
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
        sum += is_x_mas(substr, 1 + width);
    }

    std::cout << sum << std::endl;

    return 0;
}
