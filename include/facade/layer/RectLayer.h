#ifndef CHAOSEQUATIONS_RECTLAYER_H
#define CHAOSEQUATIONS_RECTLAYER_H

#include <facade/Layer.h>

namespace facade {

class RectLayer : public Layer {
public:
    glm::vec4 color;
    glm::vec2 size;

protected:
    void drawLayer(glm::mat4 matrix) override;
};

} // namespace facade

#endif // CHAOSEQUATIONS_RECTLAYER_H
