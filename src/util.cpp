#include "util.h"

#include <fstream>
#include <iostream>

void die(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

std::ifstream open_input(int argc, char *argv[])
{
    if (argc < 2) {
        die("input filename is required");
    }

    return std::ifstream(argv[1]);
}
