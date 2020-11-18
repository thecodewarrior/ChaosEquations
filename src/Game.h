#ifndef CHAOSEQUATIONS_GAME_H
#define CHAOSEQUATIONS_GAME_H

#include "SimpleRenderBuffer.h"
#include <albedo/Shader.h>
#include <albedo/opengl.h>
#include <boost/filesystem.hpp>
#include <facade/Facade.h>
#include <facade/FacadeRenderer.h>
#include <facade/GuiLayer.h>

namespace fs = boost::filesystem;

class Game {
private:
    GLFWwindow *window;
    fs::path resources_dir;
    std::shared_ptr<facade::GuiLayer> test_layer;

public:
    Game(GLFWwindow *window, fs::path resources_dir);

    ~Game();

    void run();

    void setup();

    void process_input();

    void draw_frame();
};

#endif // CHAOSEQUATIONS_GAME_H
