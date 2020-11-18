#ifndef CHAOSEQUATIONS_RECTLAYER_H
#define CHAOSEQUATIONS_RECTLAYER_H

#include <facade/GuiLayer.h>

namespace facade {

class RectLayer : public GuiLayer {
public:
    glm::vec4 color;

protected:
    void drawLayer(glm::mat4 matrix) override;
};

} // namespace facade

#endif // CHAOSEQUATIONS_RECTLAYER_H
