#include <albedo/RenderBuffer.h>
#include <facade/FacadeEnvironment.h>
#include <facade/layer/RectLayer.h>

namespace facade {

class RectRenderBuffer : public albedo::RenderBuffer {
private:
    std::shared_ptr<albedo::VertexBuffer> vbo;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 2>> pos_attr;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 4>> color_attr;

public:
    std::shared_ptr<albedo::Uniform<albedo::glsl_mat4>> transform;

    explicit RectRenderBuffer(const std::shared_ptr<albedo::Shader> &shader) : RenderBuffer(shader) {
        vbo = std::make_shared<albedo::VertexBuffer>();
        pos_attr = make_attribute<GL_FLOAT, 2>(vbo, "pos");
        color_attr = make_attribute<GL_FLOAT, 4>(vbo, "colorIn");
        transform = make_uniform<albedo::glsl_mat4>("transform");
        setup();
    }

    ALBEDO_BUFFER_BUILDER(RectRenderBuffer, pos, pos_attr)
    ALBEDO_BUFFER_BUILDER(RectRenderBuffer, color, color_attr)
};

void RectLayer::drawLayer(glm::mat4 matrix) {
    static auto rect_shader = std::make_shared<albedo::Shader>(FacadeEnvironment::resources_dir,
                                                               "shaders/rect_layer.vert", "shaders/rect_layer.frag");
    static auto rect_buffer = std::make_unique<RectRenderBuffer>(rect_shader);
    color = {1, 0, 1, 1};

    rect_buffer->transform->set(matrix);
    rect_buffer->pos(0, 0).color(color).end_vertex();
    rect_buffer->pos(size.x, 0).color(color).end_vertex();
    rect_buffer->pos(size.x, size.y).color(color).end_vertex();

    rect_buffer->pos(size.x, size.y).color(color).end_vertex();
    rect_buffer->pos(0, size.y).color(color).end_vertex();
    rect_buffer->pos(0, 0).color(color).end_vertex();

    rect_buffer->draw(GL_TRIANGLES);
}

} // namespace facade