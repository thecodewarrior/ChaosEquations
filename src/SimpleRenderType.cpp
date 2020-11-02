#include "SimpleRenderType.h"

SimpleRenderType::SimpleRenderType(const std::shared_ptr<albedo::Shader> &shader) : RenderType(shader) {
    vbo = std::make_shared<albedo::VertexBuffer>();
    pos_attr = make_attribute<GL_FLOAT, 3>(vbo, 0);
    color_attr = make_attribute<GL_FLOAT, 4>(vbo, 1);
    setup_vao();
}
