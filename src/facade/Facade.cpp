#include <facade/Facade.h>

namespace facade {

Facade::Facade() : root(std::make_shared<GuiLayer>()) {}

void Facade::update() {
    root->fire_update();
}

void Facade::draw(glm::mat4 matrix) {
    root->draw(matrix);
}

void Facade::glfw_key(int key, int scancode, int action, int mods) {
    switch(action) {
    case GLFW_PRESS:
        root->fire_key_down(key, scancode, mods);
        break;
    case GLFW_RELEASE:
        root->fire_key_up(key, scancode, mods);
        break;
    case GLFW_REPEAT:
        root->fire_key_repeat(key, scancode, mods);
        break;
    default:
        break; // never happens
    }
}

void Facade::glfw_char(unsigned int codepoint) {
    root->fire_character_typed(codepoint);
}

void Facade::glfw_cursor_pos(double xpos, double ypos) {
    glm::vec2 new_pos = {xpos, ypos};
    if(new_pos != mouse_pos) {
        root->fire_mouse_move(mouse_pos, new_pos);
        root->update_mouse_position(new_pos);
        root->hit_test(new_pos);
        mouse_pos = new_pos;
    }
}

void Facade::glfw_mouse_button(int button, int action, int mods) {
    root->hit_test(mouse_pos);
    switch(action) {
    case GLFW_PRESS:
        root->fire_mouse_down(button, mods);
        break;
    case GLFW_RELEASE:
        root->fire_mouse_up(button, mods);
        break;
    default:
        break; // never happens
    }
}

void Facade::glfw_scroll(double xoffset, double yoffset) {
    root->hit_test(mouse_pos);
    root->fire_mouse_scroll({xoffset, yoffset});
}

void Facade::glfw_framebuffer_size(int width, int height) {
    root->size = {width, height};
}

} // namespace facade
