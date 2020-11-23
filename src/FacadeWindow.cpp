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
