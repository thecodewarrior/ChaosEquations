#include "Game.h"
#include "facade/FacadeEnvironment.h"

#include <cmath>
#include <facade/layer/RectLayer.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

Game::Game(GLFWwindow *window, fs::path resources_dir) : window(window), resources_dir(std::move(resources_dir)) {
    glViewport(0, 0, 800, 600);
    facade::FacadeEnvironment::resources_dir = this->resources_dir / "facade";

    setup();
}

Game::~Game() { glfwTerminate(); }

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        process_input();
        draw_frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::setup() { test_layer = std::make_shared<facade::RectLayer>(); }

void Game::process_input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Game::draw_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    facade::Stack<glm::mat3> matrix({
        0.5, 0, 0,
        0, 0.5, 0,
        0, 0, 1.0
    });
    test_layer->draw(matrix);
}
