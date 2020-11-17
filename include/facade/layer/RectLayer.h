#ifndef CHAOSEQUATIONS_RECTLAYER_H
#define CHAOSEQUATIONS_RECTLAYER_H

#include <facade/Layer.h>

namespace facade {

class RectLayer : public Layer {
    glm::vec4 color;
    void drawLayer(Stack<glm::mat3> &matrix) override;
};

} // namespace facade

#endif // CHAOSEQUATIONS_RECTLAYER_H
