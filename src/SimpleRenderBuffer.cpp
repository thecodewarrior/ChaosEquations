#include "SimpleRenderBuffer.h"

SimpleRenderBuffer::SimpleRenderBuffer(const std::shared_ptr<albedo::Shader> &shader) : RenderBuffer(shader) {
    vbo = std::make_shared<albedo::VertexBuffer>();
    pos_attr = make_attribute<GL_FLOAT, 3>(vbo, "posIn");
    color_attr = make_attribute<GL_FLOAT, 4>(vbo, "colorIn");
    time = make_uniform<albedo::glsl_float>("time");
    setup();
}
