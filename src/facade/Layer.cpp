#include <facade/Layer.h>

namespace facade {

void Layer::draw(facade::Stack<glm::mat3> &matrix) { this->drawLayer(matrix); }

} // namespace facade
