#include "Shader.h"
#include "../common_gl.h"
#include "../utils.h"
#include "ShaderPreprocessor.h"
#include <fmt/core.h>
#include <iostream>
#include <regex>
#include <utility>

namespace albedo {

Shader::Shader(const fs::path &base_path, const fs::path &vertex_shader_name, const fs::path &fragment_shader_name) {
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    load_shader(vertex_shader_id, base_path, vertex_shader_name);
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    load_shader(fragment_shader_id, base_path, fragment_shader_name);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

Shader::~Shader() { glDeleteShader(program); }

void Shader::load_shader(unsigned int shader, const fs::path &base_path, const fs::path &name) {
    ShaderPreprocessor preprocessor(base_path, name);
    glShaderSource(shader, 1, preprocessor.c_str(), nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        char *info_log = new char[log_length];
        glGetShaderInfoLog(shader, log_length, nullptr, info_log);
        std::string log_string(info_log);
        delete[] info_log;

        std::string log = preprocessor.transform_log(log_string);

        std::cerr << "---- ERROR COMPILING SHADER ----\n";
        std::cerr << log << "\n";
        std::cerr << "---- ERROR COMPILING SHADER ----\n";
        throw ShaderCompilationException(log);
    }
}

GLint Shader::attribute_location(const std::string &name) const { return glGetAttribLocation(program, name.c_str()); }

GLint Shader::uniform_location(const std::string &name) const { return glGetUniformLocation(program, name.c_str()); }

} // namespace albedo