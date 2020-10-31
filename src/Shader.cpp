#include "Shader.h"
#include "utils.h"
#include "common_gl.h"

Shader::Shader(const fs::path &vertex_shader_path, const fs::path &fragment_shader_path) {
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    load_shader(vertex_shader_id, vertex_shader_path);
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    load_shader(fragment_shader_id, fragment_shader_path);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

void Shader::load_shader(unsigned int shader, const fs::path &source_path) {
    std::string shader_source = read_shader(source_path);
    const char *shader_c_source = shader_source.c_str();
    glShaderSource(shader, 1, &shader_c_source, nullptr);
    glCompileShader(shader);
}

std::string Shader::read_shader(const fs::path &source_path) {
    return read_file(source_path);
}
