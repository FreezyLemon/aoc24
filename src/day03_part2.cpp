#include "util.h"

#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

using std::operator""sv;

std::optional<int> parse_int(const std::string_view sv) {
    int out = 0;

    for (const char c: sv) {
        if (!std::isdigit(c)) {
            return {};
        }

        out *= 10;
        out += c - '0';
    }

    return out;
}

int main(int argc, char *argv[]) {
    auto infile = open_input(argc, argv);

    std::string content(
        (std::istreambuf_iterator<char>(infile)),
        (std::istreambuf_iterator<char>())
    );

    auto sv = std::string_view(content);
    bool enabled = true;
    int sum = 0;
    while (!sv.empty()) {
        const auto next_mul_idx = sv.find("mul("sv);

        if (!enabled) {
            const auto next_do_idx = sv.find("do()"sv);

            if (next_do_idx == std::string_view::npos) {
                break;
            }

            sv = sv.substr(4 + next_do_idx);
            enabled = true;
            continue;
        }

        const auto next_dont_idx = sv.find("don't()"sv);
        if (next_dont_idx < next_mul_idx) {
            enabled = false;
            sv = sv.substr(7 + next_dont_idx);
            continue;
        }

        if (next_mul_idx == std::string_view::npos) {
            break;
        }
        sv = sv.substr(4 + next_mul_idx);

        const auto next_comma_idx = sv.find(","sv);
        if (next_comma_idx == std::string_view::npos) {
            continue;
        }

        const auto left = parse_int(sv.substr(0, next_comma_idx));
        if (!left.has_value()) {
            continue;
        }
        sv = sv.substr(1 + next_comma_idx);

        const auto next_close_parens_idx = sv.find(")"sv);
        if (next_close_parens_idx == std::string_view::npos) {
            continue;
        }

        const auto right = parse_int(sv.substr(0, next_close_parens_idx));
        if (!right.has_value()) {
            continue;
        }
        sv = sv.substr(1 + next_close_parens_idx);

        const int mul = left.value() * right.value();
        sum += mul;
    }

    std::cout << sum << std::endl;
}