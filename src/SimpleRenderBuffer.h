#ifndef CHAOSEQUATIONS_SIMPLERENDERBUFFER_H
#define CHAOSEQUATIONS_SIMPLERENDERBUFFER_H

#include "albedo/RenderBuffer.h"

class SimpleRenderBuffer : public albedo::RenderBuffer {
private:
    std::shared_ptr<albedo::VertexBuffer> vbo;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 3>> pos_attr;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 4>> color_attr;

public:
    std::shared_ptr<albedo::Uniform<albedo::glsl_float>> time;

    explicit SimpleRenderBuffer(const std::shared_ptr<albedo::Shader> &shader);

    ALBEDO_BUFFER_BUILDER(SimpleRenderBuffer, pos, pos_attr)
    ALBEDO_BUFFER_BUILDER(SimpleRenderBuffer, color, color_attr)
};

#endif // CHAOSEQUATIONS_SIMPLERENDERBUFFER_H
