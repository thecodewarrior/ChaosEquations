#include <albedo/Shader.h>
#include <facade/FacadeEnvironment.h>
#include <facade/GuiLayer.h>
#include <liblib/Math.h>

namespace facade {

// region relationships
void GuiLayer::add(const std::shared_ptr<GuiLayer> &child) {
    children_.push_back(child);
    child->parent_ = weak_from_this();
}
void GuiLayer::remove(const std::shared_ptr<GuiLayer> &child) {
    for (auto iter = children_.cbegin(); iter != children_.end(); iter++) {
        if (*iter == child) {
            child->parent_ = {};
            children_.erase(iter);
            return;
        }
    }
}
void GuiLayer::remove_from_parent() {
    auto p = parent();
    if (p) {
        p->remove(shared_from_this());
    }
}

// region iterator
GuiLayer::iterator::iterator(std::shared_ptr<GuiLayer> parent, std::vector<std::shared_ptr<GuiLayer>> &children)
    : parent_(std::move(parent)), vec(std::make_shared<std::vector<std::shared_ptr<GuiLayer>>>(children)), index(0) {
    if (vec->empty()) {
        end = true;
    } else {
        while ((*vec)[index]->parent() != parent_) {
            ++index;
            if (index == vec->size()) {
                end = true;
                break;
            }
        }
    }
}

GuiLayer::iterator &GuiLayer::iterator::operator++() {
    if (end)
        return *this;
    do {
        ++index;
        if (index == vec->size()) {
            end = true;
            break;
        }
    } while ((*vec)[index]->parent() != parent_);
    return *this;
}
bool GuiLayer::iterator::operator==(const GuiLayer::iterator &rhs) const {
    return end == rhs.end || (index == rhs.index && vec == rhs.vec);
}
bool GuiLayer::iterator::operator!=(const GuiLayer::iterator &rhs) const {
    return end != rhs.end && (index != rhs.index || vec != rhs.vec);
}
std::shared_ptr<GuiLayer> &GuiLayer::iterator::operator*() { return (*vec)[index]; }
std::shared_ptr<GuiLayer> *GuiLayer::iterator::operator->() { return &(*vec)[index]; }

GuiLayer::iterator GuiLayer::begin() { return GuiLayer::iterator(shared_from_this(), children_); }
GuiLayer::iterator GuiLayer::end() const { return GuiLayer::iterator(); }
// endregion
// endregion

// region Rendering

void GuiLayer::draw(glm::mat4 matrix) {
    glm::mat4 local_matrix = matrix * ll::extend_transform(transform_matrix());
    this->drawLayer(local_matrix);
    for (auto &child : *this) {
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
    glm::vec2 inverse_scale(scale.x == 0 ? std::numeric_limits<float>::infinity() : 1 / scale.x,
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
