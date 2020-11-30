#ifndef CHAOSEQUATIONS_FACADEWINDOW_H
#define CHAOSEQUATIONS_FACADEWINDOW_H

#include "Window.h"
class FacadeWindow : public Window {

    std::unique_ptr<facade::Facade> facade;
    std::shared_ptr<Screen> screen;
public:
    FacadeWindow(GLFWwindow *window_handle, std::shared_ptr<Screen> screen);

protected:
    void draw() override;
    void update() override;
    void glfw_key(int key, int scancode, int action, int mods) override;
    void glfw_char(unsigned int codepoint) override;
    void glfw_cursor_pos(double xpos, double ypos) override;
    void glfw_mouse_button(int button, int action, int mods) override;
    void glfw_scroll(double xoffset, double yoffset) override;
    void glfw_framebuffer_size(int width, int height) override;
};

#endif // CHAOSEQUATIONS_FACADEWINDOW_H
