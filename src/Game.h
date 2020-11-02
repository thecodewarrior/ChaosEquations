#ifndef CHAOSEQUATIONS_GAME_H
#define CHAOSEQUATIONS_GAME_H

#include "albedo/Shader.h"
#include "common_gl.h"
#include "SimpleRenderType.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Game {
private:
    GLFWwindow *window;
    fs::path resources_dir;
    GLuint vbo;
    GLuint vao;
    std::shared_ptr<albedo::Shader> simple_shader;
    std::unique_ptr<SimpleRenderType> simple_type;
    GLint time_location;

public:
    Game(GLFWwindow *window, fs::path resources_dir);

    ~Game();

    void run();

    void setup();

    void process_input();

    void draw_frame();
};


#endif //CHAOSEQUATIONS_GAME_H
