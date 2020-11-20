#ifndef CHAOSEQUATIONS_FACADE_H
#define CHAOSEQUATIONS_FACADE_H

#include "GuiLayer.h"

namespace facade {

class Facade {
public:
    const std::shared_ptr<GuiLayer> root;

    Facade();

    void draw(glm::mat4 matrix);

    void keyPressed();
    void keyReleased();
    void characterTyped();
};

} // namespace facade

#endif // CHAOSEQUATIONS_FACADE_H
