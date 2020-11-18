#include <albedo/Shader.h>
#include <facade/FacadeEnvironment.h>
#include <facade/GuiLayer.h>
#include <liblib/Math.h>

namespace facade {

void GuiLayer::add(std::shared_ptr<GuiLayer> child) {
    children_.push_back(child);
    child->parent_ = weak_from_this();
}
void GuiLayer::remove(std::shared_ptr<GuiLayer> child) {
    for(auto iter = children_.cbegin(); iter != children_.end(); iter++) {
        if(*iter == child) {
            child->parent_ = {};
            children_.erase(iter);
            return;
        }
    }
}
void GuiLayer::remove_from_parent() {
    auto p = parent().lock();
    if(p) {
        p->remove(shared_from_this());
    }
}

// region Rendering

void GuiLayer::draw(glm::mat4 matrix) {
    glm::mat4 local_matrix = matrix * ll::extend_transform(transform_matrix());
    this->drawLayer(local_matrix);
    for(auto &child : children_) {
        child->draw(local_matrix);
    }
}

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
        scale.y == 0 ? std::numeric_limits<float>::infinity() : 1 / scale.y);
    auto m = ll::identity<glm::mat3>();
    m = ll::translate(m, anchor * size);
    m = ll::scale(m, inverse_scale);
    m = ll::rotate(m, -rotation);
    m = ll::translate(m, -pos);
    return m;
}

// endregion

} // namespace facade
