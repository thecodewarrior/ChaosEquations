#ifndef CHAOSEQUATIONS_WINDOW_H
#define CHAOSEQUATIONS_WINDOW_H

#include "Screen.h"
#include "SimpleRenderBuffer.h"
#include <albedo/Shader.h>
#include <albedo/opengl.h>
#include <boost/filesystem.hpp>
#include <facade/Facade.h>
#include <facade/FacadeRenderer.h>
#include <facade/GuiLayer.h>
#include <liblib/utils.h>

namespace fs = boost::filesystem;

class Window {
private:
    GLFWwindow *window_handle;
    ll::spin_sleep_clock::duration frame_duration;

public:
    explicit Window(GLFWwindow *window_handle);
    ~Window();

    void run();

protected:
    void set_framerate(int fps);

    virtual void update() {}
    virtual void draw() {}
    virtual void glfw_key(int key, int scancode, int action, int mods) {}
    virtual void glfw_char(unsigned int codepoint) {}
    virtual void glfw_cursor_pos(double xpos, double ypos) {}
    virtual void glfw_mouse_button(int button, int action, int mods) {}
    virtual void glfw_scroll(double xoffset, double yoffset) {}
    virtual void glfw_framebuffer_size(int width, int height) {}

private:
    inline static void _glfw_key_callback(GLFWwindow *window_handle, int key, int scancode, int action, int mods) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_key(key, scancode, action, mods);
    }
    inline static void _glfw_char_callback(GLFWwindow *window_handle, unsigned int codepoint) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_char(codepoint);
    }
    inline static void _glfw_cursor_pos_callback(GLFWwindow *window_handle, double xpos, double ypos) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_cursor_pos(xpos, ypos);
    }
    inline static void _glfw_mouse_button_callback(GLFWwindow *window_handle, int button, int action, int mods) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_mouse_button(button, action, mods);
    }
    inline static void _glfw_scroll_callback(GLFWwindow *window_handle, double xoffset, double yoffset) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_scroll(xoffset, yoffset);
    }
    inline static void _glfw_framebuffer_size_callback(GLFWwindow *window_handle, int width, int height) {
        auto *window = static_cast<Window *>(glfwGetWindowUserPointer(window_handle));
        window->glfw_framebuffer_size(width, height);
    }
};

#endif // CHAOSEQUATIONS_WINDOW_H
