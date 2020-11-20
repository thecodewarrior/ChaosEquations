#include "Window.h"
#include "facade/FacadeEnvironment.h"

#include <cmath>
#include <utility>
#include <facade/layer/RectLayer.h>
#include <liblib/Colors.h>
#include <liblib/Math.h>

Window::Window(GLFWwindow *window, const std::shared_ptr<Screen>& screen)
    : window(window), screen(screen), facade(std::make_unique<facade::Facade>()) {
    glViewport(0, 0, 800, 600);

    facade->root->add(this->screen->root);
    setup_callbacks();
}

Window::~Window() { glfwTerminate(); }

void Window::setup_callbacks() {}

void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        process_input();
        draw_frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::process_input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::draw_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 projection_matrix = glm::ortho<float>(0, 800, 600, 0, -100, 100);
    // flipping the Y axis flips the handedness, so the winding has to flip to remain logically CCW
    glFrontFace(GL_CW);

    facade->draw(projection_matrix);
}
