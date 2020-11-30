#ifndef CHAOSEQUATIONS_GUILAYER_H
#define CHAOSEQUATIONS_GUILAYER_H

#include "CoordinateSpace.h"
#include <albedo/Shader.h>
#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>
#include <facade/FacadeEnvironment.h>
#include <glm/glm.hpp>
#include <vector>

namespace facade {
namespace fs = boost::filesystem;
namespace sig = boost::signals2;

/// The fundamental unit of a Facade GUI.
///
/// Layers can be iterated using `for(auto child : *layer)`. When iterating like this, any children added during
/// iteration will not be included, and any removed during iteration will be skipped
class GuiLayer : public std::enable_shared_from_this<GuiLayer>,
                 public CoordinateSpace<2, float, glm::qualifier::defaultp> {
public:
    GuiLayer() = default;
    GuiLayer(const GuiLayer &) = delete;

    GuiLayer(float x, float y) : pos({x, y}) {}
    explicit GuiLayer(glm::vec2 pos) : pos(pos) {}
    GuiLayer(float x, float y, float w, float h) : pos({x, y}), size({w, h}) {}
    GuiLayer(glm::vec2 pos, glm::vec2 size) : pos(pos), size(size) {}

    // region geometry
public:
    glm::vec2 pos{0, 0};
    glm::vec2 size{0, 0};
    float rotation{0};
    glm::vec2 scale{1, 1};
    glm::vec2 anchor{0, 0};

    /// Computes the transform matrix based on the current geometry parameters.
    ///
    /// @return The matrix taking points from this layer's coordinate space to its parent's coordinate space.
    [[nodiscard]] glm::mat3 transform_matrix() const override;

    /// Computes the inverse transform matrix based on the current geometry parameters.
    ///
    /// @return The matrix taking points from the parent's coordinate space to this layer's coordinate space.
    [[nodiscard]] glm::mat3 inverse_transform_matrix() const override;

protected:
    space_type *parent_space() const override;
    // endregion

    // region relationships
private:
    std::weak_ptr<GuiLayer> parent_;
    std::vector<std::shared_ptr<GuiLayer>> children_;

public:
    void add(const std::shared_ptr<GuiLayer> &child);
    void remove(const std::shared_ptr<GuiLayer> &child);

    /// Remove this layer from its parent
    void remove_from_parent();

    std::shared_ptr<GuiLayer> parent() const { return parent_.lock(); }

    /// True if this layer is the root of its hierarchy (i.e. has no parent)
    bool is_root() const;

    // region iterator
    class iterator {
        bool end = false;
        int index = 0;
        std::shared_ptr<GuiLayer> parent_;
        std::shared_ptr<std::vector<std::shared_ptr<GuiLayer>>> vec;

    public:
        typedef ptrdiff_t difference_type;
        typedef GuiLayer value_type;
        typedef GuiLayer *pointer;
        typedef GuiLayer &reference;
        typedef std::input_iterator_tag iterator_category;

        iterator() : end(true) {}
        iterator(std::shared_ptr<GuiLayer> parent, std::vector<std::shared_ptr<GuiLayer>> &children);
        iterator(const iterator &other) = default;

        iterator &operator++();
        bool operator==(const iterator &rhs) const;
        bool operator!=(const iterator &rhs) const;
        std::shared_ptr<GuiLayer> &operator*();
        std::shared_ptr<GuiLayer> *operator->();
    };

    /// Iterate the children of this layer. Any children added during iteration will not be iterated, and any removed
    /// during iteration will be skipped.
    iterator begin();
    iterator end() const;
    // endregion
    // endregion

    // region rendering
public:
    void draw(glm::mat4 matrix);

protected:
    virtual void drawLayer(glm::mat4 matrix) {}

    template <typename T>
    static std::unique_ptr<T> make_buffer(const fs::path &vertex_shader_name, const fs::path &fragment_shader_name) {
        auto shader = std::make_shared<albedo::Shader>(FacadeEnvironment::resources_dir, vertex_shader_name,
                                                       fragment_shader_name);
        return std::make_unique<T>(shader);
    }

    // endregion

    // region base
public:
    sig::signal<void()> on_update;
    void fire_update();

protected:
    template <typename T> std::shared_ptr<T> shared_from_this_as() {
        return std::static_pointer_cast<T>(shared_from_this());
    }

    template <typename T> std::shared_ptr<const T> shared_from_this_as() const {
        return std::static_pointer_cast<const T>(shared_from_this());
    }

    template <typename T> std::weak_ptr<T> weak_from_this_as() {
        return std::static_pointer_cast<T>(weak_from_this().lock());
    }

    template <typename T> std::weak_ptr<const T> weak_from_this_as() const {
        return std::static_pointer_cast<const T>(weak_from_this().lock());
    }
    // endregion

    // region input
public:
    typedef void key_event(int key, int scancode, int mods);
    sig::signal<key_event> on_key_down;
    sig::signal<key_event> on_key_up;
    sig::signal<key_event> on_key_repeat;
    sig::signal<void(unsigned int codepoint)> on_character_typed;

    typedef void mouse_event(int button, int mods);
    sig::signal<void(glm::vec2 old_pos, glm::vec2 new_pos)> on_mouse_move;
    sig::signal<mouse_event> on_mouse_down;
    sig::signal<mouse_event> on_mouse_up;
    sig::signal<void(glm::vec2 offset)> on_mouse_scroll;

    /// The mouse position in this layer
    glm::vec2 mouse_pos{0, 0};
    /// Whether the mouse is inside this layer's bounds
    bool mouse_inside;
    /// Whether the mouse is over this layer
    bool mouse_over;

    /// Whether to ignore this layer's bounds when computing mouse hits
    bool ignore_mouse_over_bounds = false;
    /// Whether this layer's mouse_over flag propagates to its parent
    bool propagates_mouse_over = true;

    /// Internal - fires the key_down event and then calls fire_keydown on its children
    void fire_key_down(int key, int scancode, int mods);
    /// Internal - fires the key_up event and then calls fire_keyup on its children
    void fire_key_up(int key, int scancode, int mods);
    /// Internal - fires the key_repeat event and then calls fire_keyrepeat on its children
    void fire_key_repeat(int key, int scancode, int mods);
    /// Internal - fires the character_typed event and then calls fire_character_typed on its children
    void fire_character_typed(unsigned int codepoint);

    /// Internal - fires the mouse_move event and then calls fire_mousemove on its children
    ///
    /// @param old_pos The old position in the parent's coordinate space
    /// @param new_pos The new position in the parent's coordinate space
    void fire_mouse_move(glm::vec2 old_pos, glm::vec2 new_pos);
    /// Internal - fires the mouse_down event and then calls fire_mousedown on its children
    void fire_mouse_down(int button, int mods);
    /// Internal - fires the mouse_up event and then calls fire_mouseup on its children
    void fire_mouse_up(int button, int mods);
    /// Internal - fires the mouse_scroll event and then calls fire_mouse_scroll on its children
    ///
    /// @param offset The offset in the parent's coordinate space
    void fire_mouse_scroll(glm::vec2 offset);

    /// Internal - updates the mouse position and mouse_inside flags.
    ///
    /// @param position the position of the mouse in the parent's coordinate space
    void update_mouse_position(glm::vec2 position);

    /// Internal - returns the layer the mouse is directly over
    ///
    /// @param point The point to hit test in the parent's coordinate space
    /// @return The layer that the mouse hit
    std::shared_ptr<GuiLayer> hit_test(glm::vec2 point);
    // endregion
};

} // namespace facade

#endif // CHAOSEQUATIONS_GUILAYER_H
