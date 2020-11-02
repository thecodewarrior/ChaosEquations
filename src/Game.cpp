#include "Game.h"
#include "utils.h"

#include <cmath>
#include <glm/vec2.hpp>

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

    simple_shader = std::make_shared<albedo::Shader>(resources_dir, "simple.vert", "simple.frag");
    simple_type = std::make_unique<SimpleRenderType>(simple_shader);

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

    simple_type->pos(-0.5, -0.5, 0.0).color(1, 0, 0, 1).end_vertex();
    simple_type->pos( 0.5, -0.5, 0.0).color(0, 1, 0, 1).end_vertex();
    simple_type->pos( 0.0,  0.5, 0.0).color(0, 0, 1, 1).end_vertex();
    simple_type->draw(GL_TRIANGLES);
}
