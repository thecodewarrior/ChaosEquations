#ifndef CHAOSEQUATIONS_SHADER_H
#define CHAOSEQUATIONS_SHADER_H

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Shader {
public:
    unsigned int program;
    Shader(const fs::path &vertex_shader_path, const fs::path &fragment_shader_path);

private:
    static void load_shader(unsigned int shader, const fs::path &source_path);

    static std::string read_shader(const fs::path &source_path);
};


#endif //CHAOSEQUATIONS_SHADER_H
