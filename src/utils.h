#ifndef CHAOSEQUATIONS_UTILS_H
#define CHAOSEQUATIONS_UTILS_H

#include <string>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::string read_file(const fs::path& path);

#endif //CHAOSEQUATIONS_UTILS_H
