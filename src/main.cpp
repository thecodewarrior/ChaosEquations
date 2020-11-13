#include <boost/filesystem.hpp>

#include "Game.h"
#include "common_gl.h"
#include <iostream>

namespace fs = boost::filesystem;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Missing resources directory parameter";
        return 1;
    }

    // this is provided by the dev environment and later by the bundle bootstrap script.
    fs::path resources_dir(argv[1]);

    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    Game *game = new Game(window, resources_dir);

    game->run();

    delete game;
    return 0;
}
