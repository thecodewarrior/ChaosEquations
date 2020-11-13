#include "utils.h"

std::string read_file(const fs::path &path) {
    fs::ifstream ifs(path);
    return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}
