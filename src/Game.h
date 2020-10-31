#ifndef CHAOSEQUATIONS_GAME_H
#define CHAOSEQUATIONS_GAME_H

#include "Shader.h"
#include "common_gl.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Game {
private:
    GLFWwindow *window;
    fs::path resources_dir;
    GLuint vbo;
    GLuint vao;
    std::unique_ptr<Shader> simple_shader;
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
