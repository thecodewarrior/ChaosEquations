#include <facade/Facade.h>

namespace facade {

Facade::Facade() : root(std::make_shared<GuiLayer>()) {}

void Facade::draw(glm::mat4 matrix) { root->draw(matrix); }

} // namespace facade
