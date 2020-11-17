#ifndef CHAOSEQUATIONS_SHADERPREPROCESSOR_H
#define CHAOSEQUATIONS_SHADERPREPROCESSOR_H

#include "opengl.h"
#include <boost/filesystem.hpp>
#include <sstream>
#include <vector>

namespace albedo {
namespace fs = boost::filesystem;
class ShaderPreprocessor {
private:
    fs::path base_path;
    std::map<fs::path, int> ids;
    std::vector<fs::path> stack;
    std::stringstream out;
    std::string result;
    const char *c_result;

public:
    ShaderPreprocessor(fs::path base_path, const fs::path &name);

    std::string str() const;
    const GLchar *const *c_str() const;

    std::string transform_log(const std::string &source);

private:
    void load_file(const fs::path &name);

    static const int source_number_base = 31500;
};

class ShaderPreprocessException : public std::exception {
private:
    std::string message;

public:
    explicit ShaderPreprocessException(std::string message) : message(std::move(message)) {}

    [[nodiscard]] const char *what() const _NOEXCEPT override { return message.c_str(); }
};
} // namespace albedo

#endif // CHAOSEQUATIONS_SHADERPREPROCESSOR_H
