#ifndef CHAOSEQUATIONS_SHADER_H
#define CHAOSEQUATIONS_SHADER_H

#include <sstream>
#include <utility>
#include <vector>
#include <boost/filesystem.hpp>
#include "../common_gl.h"

namespace albedo {
    namespace fs = boost::filesystem;

    class Shader {
    public:
        GLuint program;

        Shader(const fs::path &base_path, const fs::path &vertex_shader_name, const fs::path &fragment_shader_name);

        ~Shader();

        [[nodiscard]] GLint attribute_location(const std::string &name) const;

        [[nodiscard]] GLint uniform_location(const std::string &name) const;

    private:
        static void load_shader(unsigned int shader, const fs::path &base_path, const fs::path &name);
    };

    class ShaderCompilationException : public std::exception {
    private:
        std::string message;
    public:
        explicit ShaderCompilationException(std::string message) : message(std::move(message)) {}

        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return message.c_str();
        }
    };
}


#endif //CHAOSEQUATIONS_SHADER_H
