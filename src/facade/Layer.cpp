#include <facade/Layer.h>
#include <liblib/Math.h>

namespace facade {

void Layer::draw(glm::mat4 matrix) { this->drawLayer(matrix * transform_matrix_4x4()); }
glm::mat3 Layer::transform_matrix() const {
    return ll::translate(ll::identity<glm::mat3>(), pos);
}
glm::mat4 Layer::transform_matrix_4x4() const {
    glm::mat3 transform = transform_matrix();
    return {{transform[0][0], transform[0][1], 0, 0},
            {transform[1][0], transform[1][1], 0, 0},
            {0, 0, 1, 0},
            {transform[2][0], transform[2][1], 0, 1}};
}

} // namespace facade
