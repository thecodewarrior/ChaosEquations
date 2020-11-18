#include <albedo/Shader.h>
#include <facade/FacadeEnvironment.h>
#include <facade/GuiLayer.h>
#include <liblib/Math.h>

namespace facade {

void GuiLayer::draw(glm::mat4 matrix) { this->drawLayer(matrix * ll::extend_transform(transform_matrix())); }

glm::mat3 GuiLayer::transform_matrix() const {
    auto m = ll::identity<glm::mat3>();
    m = ll::translate(m, pos);
    m = ll::rotate(m, rotation);
    m = ll::scale(m, scale);
    m = ll::translate(m, -anchor * size);
    return m;
}
glm::mat3 GuiLayer::inverse_transform_matrix() const {
    glm::vec2 inverse_scale( //
        scale.x == 0 ? std::numeric_limits<float>::infinity() : 1 / scale.x,
        scale.y == 0 ? std::numeric_limits<float>::infinity() : 1 / scale.y
    );
    auto m = ll::identity<glm::mat3>();
    m = ll::translate(m, anchor * size);
    m = ll::scale(m, inverse_scale);
    m = ll::rotate(m, -rotation);
    m = ll::translate(m, -pos);
    return m;
}

//template <typename T>
//std::unique_ptr<T> GuiLayer::make_buffer(const fs::path &vertex_shader_name, const fs::path &fragment_shader_name) {
//    auto shader =
//        std::make_shared<albedo::Shader>(FacadeEnvironment::resources_dir, vertex_shader_name, fragment_shader_name);
//    return std::make_unique<T>(shader);
//}

} // namespace facade
