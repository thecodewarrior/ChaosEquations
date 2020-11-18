#ifndef CHAOSEQUATIONS_GUILAYER_H
#define CHAOSEQUATIONS_GUILAYER_H

#include <albedo/Shader.h>
#include <boost/filesystem.hpp>
#include <facade/FacadeEnvironment.h>
#include <glm/glm.hpp>
#include <vector>

namespace facade {
namespace fs = boost::filesystem;

class GuiLayer {
public:
    glm::vec2 pos{0, 0};
    glm::vec2 size{0, 0};
    float rotation{0};
    glm::vec2 scale{1, 1};
    glm::vec2 anchor{0, 0};

    void draw(glm::mat4 matrix);

protected:
    virtual void drawLayer(glm::mat4 matrix) {}

    template <typename T>
    static std::unique_ptr<T> make_buffer(const fs::path &vertex_shader_name, const fs::path &fragment_shader_name) {
        auto shader = std::make_shared<albedo::Shader>(FacadeEnvironment::resources_dir, vertex_shader_name,
                                                       fragment_shader_name);
        return std::make_unique<T>(shader);
    }

private:
    [[nodiscard]] glm::mat3 transform_matrix() const;
    [[nodiscard]] glm::mat3 inverse_transform_matrix() const;
};

} // namespace facade

#endif // CHAOSEQUATIONS_GUILAYER_H
