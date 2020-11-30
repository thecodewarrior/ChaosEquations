#ifndef CHAOSEQUATIONS_FACADE_H
#define CHAOSEQUATIONS_FACADE_H

#include "GuiLayer.h"

namespace facade {

class Facade {
private:
    glm::vec2 mouse_pos{0, 0};

public:
    const std::shared_ptr<GuiLayer> root;

    Facade();

    void update();
    void draw(glm::mat4 matrix);

    void glfw_key(int key, int scancode, int action, int mods);
    void glfw_char(unsigned int codepoint);
    void glfw_cursor_pos(double xpos, double ypos);
    void glfw_mouse_button(int button, int action, int mods);
    void glfw_scroll(double xoffset, double yoffset);
    void glfw_framebuffer_size(int width, int height);
};

} // namespace facade

#endif // CHAOSEQUATIONS_FACADE_H
