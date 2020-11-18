#ifndef CHAOSEQUATIONS_LAYER_H
#define CHAOSEQUATIONS_LAYER_H

#include <glm/glm.hpp>
#include <vector>

namespace facade {

class Layer {
public:
    glm::vec2 pos;

    void draw(glm::mat4 matrix);


protected:
    virtual void drawLayer(glm::mat4 matrix) {}

private:
    [[nodiscard]] glm::mat3 transform_matrix() const;
    [[nodiscard]] glm::mat4 transform_matrix_4x4() const;
};

} // namespace facade

#endif // CHAOSEQUATIONS_LAYER_H
