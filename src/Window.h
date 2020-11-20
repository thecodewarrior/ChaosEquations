#ifndef CHAOSEQUATIONS_WINDOW_H
#define CHAOSEQUATIONS_WINDOW_H

#include "Screen.h"
#include "SimpleRenderBuffer.h"
#include <albedo/Shader.h>
#include <albedo/opengl.h>
#include <boost/filesystem.hpp>
#include <facade/Facade.h>
#include <facade/FacadeRenderer.h>
#include <facade/GuiLayer.h>

namespace fs = boost::filesystem;

class Window {
private:
    GLFWwindow *window;

public:
    std::unique_ptr<facade::Facade> facade;
    std::shared_ptr<Screen> screen;

    Window(GLFWwindow *window, const std::shared_ptr<Screen>& screen);
    ~Window();

    void run();

private:
    void setup_callbacks();

    void process_input();

    void draw_frame();
};

#endif // CHAOSEQUATIONS_WINDOW_H
