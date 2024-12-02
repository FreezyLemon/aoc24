#include <fstream>
#include <string>

// Prints an error messages and exits with exit code 1.
void die(const std::string& msg);

std::ifstream open_input(int argc, char *argv[]);
