#ifndef CHAOSEQUATIONS_LAYER_H
#define CHAOSEQUATIONS_LAYER_H

#include "Math.h"
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace facade {

class Layer {
public:
    glm::vec2 pos;

    void draw(Stack<glm::mat3> &matrix);

protected:
    virtual void drawLayer(Stack<glm::mat3> &matrix) {}
};

} // namespace facade

#endif // CHAOSEQUATIONS_LAYER_H
