#include "util.h"

#include <iostream>

void die(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
