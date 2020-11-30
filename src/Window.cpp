#include "Window.h"

#include <facade/layer/RectLayer.h>
#include <utility>

Window::Window(GLFWwindow *window_handle) : window_handle(window_handle) {
    set_framerate(60);
    glViewport(0, 0, 800, 600);

    glfwSetWindowUserPointer(window_handle, this);

    glfwSetKeyCallback(window_handle, _glfw_key_callback);
    glfwSetCharCallback(window_handle, _glfw_char_callback);
    glfwSetCursorPosCallback(window_handle, _glfw_cursor_pos_callback);
    glfwSetMouseButtonCallback(window_handle, _glfw_mouse_button_callback);
    glfwSetScrollCallback(window_handle, _glfw_scroll_callback);
    glfwSetFramebufferSizeCallback(window_handle, _glfw_framebuffer_size_callback);
}

Window::~Window() { glfwTerminate(); }

void Window::set_framerate(int fps) {
    using namespace std::chrono;
    frame_duration = duration_cast<ll::spin_sleep_clock::duration>(seconds(1)) / fps;
}

void Window::run() {
    while (!glfwWindowShouldClose(window_handle)) {
        auto next_frame = ll::spin_sleep_clock::now() + frame_duration;

        update();
        draw();

        glfwSwapBuffers(window_handle);
        glfwPollEvents();

        ll::spin_sleep_until(next_frame);
    }
}
