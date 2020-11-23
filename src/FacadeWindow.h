#ifndef CHAOSEQUATIONS_FACADEWINDOW_H
#define CHAOSEQUATIONS_FACADEWINDOW_H

#include "Window.h"
class FacadeWindow : public Window {

    std::unique_ptr<facade::Facade> facade;
    std::shared_ptr<Screen> screen;
public:
    FacadeWindow(GLFWwindow *window_handle, std::shared_ptr<Screen> screen);

protected:
    void draw() override;
};

#endif // CHAOSEQUATIONS_FACADEWINDOW_H
