#include "Game.h"
#include "facade/FacadeEnvironment.h"

#include <cmath>
#include <facade/layer/RectLayer.h>
#include <liblib/Math.h>
#include <liblib/Colors.h>

Game::Game(GLFWwindow *window, fs::path resources_dir) : window(window), resources_dir(std::move(resources_dir)) {
    glViewport(0, 0, 800, 600);
    facade::FacadeEnvironment::resources_dir = this->resources_dir / "facade";

    setup();
}

Game::~Game() { glfwTerminate(); }

void Game::setup() {
    auto rect = std::make_shared<facade::RectLayer>();
    rect->color = ll::colors::red;
    rect->size = {100, 100};
    rect->pos = {100, 100};
    rect->rotation = glm::radians(15.);
    rect->scale.y = 1.5;

    auto child = std::make_shared<facade::RectLayer>();
    child->color = ll::colors::blue;
    child->size = {50, 50};
    child->pos = {75, 25};

    rect->add(child);

    test_layer = rect;
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        process_input();
        draw_frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::process_input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Game::draw_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 projection_matrix = glm::ortho<float>(0, 800, 600, 0, -100, 100);
    // flipping the Y axis flips the handedness, so the winding has to flip to remain logically CCW
    glFrontFace(GL_CW);

    test_layer->draw(projection_matrix);
}
