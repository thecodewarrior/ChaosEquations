#include <albedo/Shader.h>
#include <facade/FacadeEnvironment.h>
#include <facade/GuiLayer.h>
#include <liblib/Math.h>

namespace facade {

// region Geometry
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

bool GuiLayer::is_root() const { return parent() == nullptr; }

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

// endregion

// region Base
void GuiLayer::fire_update() {
    auto iter = this->begin();
    on_update();
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_update();
    }
}
// endregion

// region input
void GuiLayer::fire_key_down(int key, int scancode, int mods) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_key_down(key, scancode, mods);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_key_down(key, scancode, mods);
    }
}

void GuiLayer::fire_key_up(int key, int scancode, int mods) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_key_up(key, scancode, mods);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_key_up(key, scancode, mods);
    }
}

void GuiLayer::fire_key_repeat(int key, int scancode, int mods) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_key_repeat(key, scancode, mods);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_key_repeat(key, scancode, mods);
    }
}

void GuiLayer::fire_character_typed(unsigned int codepoint) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_character_typed(codepoint);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_character_typed(codepoint);
    }
}

void GuiLayer::fire_mouse_move(glm::vec2 old_pos, glm::vec2 new_pos) {
    auto local_old_pos = convert_from_parent(old_pos);
    auto local_new_pos = convert_from_parent(new_pos);
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_mouse_move(old_pos, new_pos);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_mouse_move(local_old_pos, local_new_pos);
    }
}
void GuiLayer::fire_mouse_down(int button, int mods) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_mouse_down(button, mods);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_mouse_down(button, mods);
    }
}
void GuiLayer::fire_mouse_up(int button, int mods) {
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_mouse_up(button, mods);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_mouse_up(button, mods);
    }
}
void GuiLayer::fire_mouse_scroll(glm::vec2 offset) {
    auto local_offset = convert_from_parent(offset, 0);
    // prevent infinite loops if a layer adds one of itself to itself during the event.
    auto iter = this->begin();
    on_mouse_scroll(local_offset);
    for (; iter != this->end(); ++iter) {
        iter->get()->fire_mouse_scroll(local_offset);
    }
}

void GuiLayer::update_mouse_position(glm::vec2 position) {
    auto local_pos = convert_from_parent(position);
    mouse_pos = local_pos;
    mouse_inside = local_pos.x >= 0 && local_pos.y >= 0 && local_pos.x < size.x && local_pos.y < size.y;
    mouse_over = false;
    for (auto &child : *this) {
        child->update_mouse_position(local_pos);
    }
    if (is_root()) {
        auto mouse_over_layer = this->hit_test(position);
        while (mouse_over_layer != nullptr) {
            mouse_over_layer->mouse_over = true;
            if (!mouse_over_layer->propagates_mouse_over) {
                break;
            }
            mouse_over_layer = mouse_over_layer->parent();
        }
    }
}

std::shared_ptr<GuiLayer> GuiLayer::hit_test(glm::vec2 point) {
    auto local_point = convert_from_parent(point);
    auto is_point_inside = !ignore_mouse_over_bounds && local_point.x >= 0 && local_point.y >= 0 &&
                           local_point.x < size.x && local_point.y < size.y;
    auto hit = is_point_inside ? shared_from_this() : std::shared_ptr<GuiLayer>();
    for (auto &child : *this) {
        auto child_hit = child->hit_test(local_point);
        if (child_hit != nullptr) {
            hit = child_hit;
        }
    }
    return hit;
}

GuiLayer::space_type *GuiLayer::parent_space() const { return parent().get(); }
// endregion

} // namespace facade
