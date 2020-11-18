#ifndef CHAOSEQUATIONS_GUILAYER_H
#define CHAOSEQUATIONS_GUILAYER_H

#include <albedo/Shader.h>
#include <boost/filesystem.hpp>
#include <facade/FacadeEnvironment.h>
#include <glm/glm.hpp>
#include <vector>

namespace facade {
namespace fs = boost::filesystem;

class GuiLayer : public std::enable_shared_from_this<GuiLayer> {
private:
    std::weak_ptr<GuiLayer> parent_;
    std::vector<std::shared_ptr<GuiLayer>> children_;

public:
    glm::vec2 pos{0, 0};
    glm::vec2 size{0, 0};
    float rotation{0};
    glm::vec2 scale{1, 1};
    glm::vec2 anchor{0, 0};

    void add(std::shared_ptr<GuiLayer> child);
    void remove(std::shared_ptr<GuiLayer> child);

    /// Remove this layer from its parent
    void remove_from_parent();

    const std::weak_ptr<GuiLayer> &parent() { return parent_; }

    void draw(glm::mat4 matrix);

    GuiLayer() = default;
    GuiLayer(float x, float y) : pos({x, y}) {}
    GuiLayer(float x, float y, float w, float h) : pos({x, y}), size({w, h}) {}

    GuiLayer(glm::vec2 pos) : pos(pos) {}
    GuiLayer(glm::vec2 pos, glm::vec2 size) : pos(pos), size(size) {}
    GuiLayer(const GuiLayer &) = delete;

protected:
    virtual void drawLayer(glm::mat4 matrix) {}

    template <typename T>
    static std::unique_ptr<T> make_buffer(const fs::path &vertex_shader_name, const fs::path &fragment_shader_name) {
        auto shader = std::make_shared<albedo::Shader>(FacadeEnvironment::resources_dir, vertex_shader_name,
                                                       fragment_shader_name);
        return std::make_unique<T>(shader);
    }

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

private:
    [[nodiscard]] glm::mat3 transform_matrix() const;
    [[nodiscard]] glm::mat3 inverse_transform_matrix() const;
};

} // namespace facade

#endif // CHAOSEQUATIONS_GUILAYER_H
