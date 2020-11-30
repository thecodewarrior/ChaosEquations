#include "FacadeWindow.h"

#include <utility>

FacadeWindow::FacadeWindow(GLFWwindow *window_handle, std::shared_ptr<Screen> screen)
    : Window(window_handle), screen(std::move(screen)), facade(std::make_unique<facade::Facade>()) {

    facade->root->add(this->screen->root);
}

void FacadeWindow::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 projection_matrix = glm::ortho<float>(0, 800, 600, 0, -100, 100);
    // flipping the Y axis flips the handedness, so the winding has to flip to remain logically CCW
    glFrontFace(GL_CW);

    facade->draw(projection_matrix);
}
void FacadeWindow::update() { facade->update(); }
void FacadeWindow::glfw_key(int key, int scancode, int action, int mods) {
    facade->glfw_key(key, scancode, action, mods);
}
void FacadeWindow::glfw_char(unsigned int codepoint) { facade->glfw_char(codepoint); }
void FacadeWindow::glfw_cursor_pos(double xpos, double ypos) { facade->glfw_cursor_pos(xpos, ypos); }
void FacadeWindow::glfw_mouse_button(int button, int action, int mods) {
    facade->glfw_mouse_button(button, action, mods);
}
void FacadeWindow::glfw_scroll(double xoffset, double yoffset) { facade->glfw_scroll(xoffset, yoffset); }
void FacadeWindow::glfw_framebuffer_size(int width, int height) { facade->glfw_framebuffer_size(width, height); }
