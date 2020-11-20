#ifndef CHAOSEQUATIONS_SCREEN_H
#define CHAOSEQUATIONS_SCREEN_H

#include <memory>
#include <facade/GuiLayer.h>

class Screen {
public:
    std::shared_ptr<facade::GuiLayer> root;

    Screen(): root(std::make_shared<facade::GuiLayer>()) {}
};

#endif // CHAOSEQUATIONS_SCREEN_H
