#include <boost/filesystem.hpp>

#include "FacadeWindow.h"
#include "TestScreen.h"
#include "Window.h"
#include <albedo/opengl.h>
#include <iostream>

namespace fs = boost::filesystem;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Missing resources directory argument";
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

    GLFWwindow *window_handle = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window_handle == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window_handle);

    facade::FacadeEnvironment::resources_dir = resources_dir / "facade";

    auto screen = std::make_shared<TestScreen>();
    auto window = std::make_unique<FacadeWindow>(window_handle, screen);

    window->run();

    return 0;
}
