#include "Game.h"
#include "utils.h"

#include <cmath>

Game::Game(GLFWwindow *window, fs::path resources_dir) : window(window), resources_dir(std::move(resources_dir)) {
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    setup();
}

Game::~Game() {
    glfwTerminate();
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        process_input();
        draw_frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::setup() {
    float vertices[]{
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0, 0.5, 0.0
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    simple_shader = std::make_unique<Shader>(resources_dir / "simple.vert", resources_dir / "simple.frag");

    glUseProgram(simple_shader->program);

    time_location = glGetUniformLocation(simple_shader->program, "time");


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void Game::process_input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Game::draw_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(simple_shader->program);
    float timeValue = glfwGetTime();
    glUniform1f(time_location, timeValue);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
