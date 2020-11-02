#ifndef CHAOSEQUATIONS_SIMPLERENDERTYPE_H
#define CHAOSEQUATIONS_SIMPLERENDERTYPE_H


#include "albedo/RenderType.h"

class SimpleRenderType : public albedo::RenderType {
private:
    std::shared_ptr<albedo::VertexBuffer> vbo;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 3>> pos_attr;
    std::shared_ptr<albedo::VertexAttribute<GL_FLOAT, 4>> color_attr;

public:
    explicit SimpleRenderType(const std::shared_ptr<albedo::Shader> &shader);

    RENDER_TYPE_BUILDER(SimpleRenderType, pos, pos_attr)
    RENDER_TYPE_BUILDER(SimpleRenderType, color, color_attr)

};


#endif //CHAOSEQUATIONS_SIMPLERENDERTYPE_H
