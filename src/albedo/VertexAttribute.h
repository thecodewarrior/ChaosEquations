#ifndef CHAOSEQUATIONS_VERTEXATTRIBUTE_H
#define CHAOSEQUATIONS_VERTEXATTRIBUTE_H

#include "VertexBuffer.h"
#include "uniform_type.h"
#include <memory>
#include <string>

namespace albedo {
class VertexAttributeBase {
public:
    GLint location = -1;
    const std::string name;
    const std::shared_ptr<VertexBuffer> buffer;
    const size_t size;
    const size_t offset;

    VertexAttributeBase(const std::shared_ptr<VertexBuffer> &buffer, std::string name, int size);

    void setup_vao() const {
        if (location == -1)
            return; // glGetAttribLocation returns -1 when the attribute isn't active
        buffer->bind();
        setup_attrib_pointer();
        glEnableVertexAttribArray(location);
    }

protected:
    virtual void setup_attrib_pointer() const {}
};

template <GLenum G, int C> class VertexAttribute {};

enum IntAttributeKind { ATTR_KIND_FLOAT, ATTR_KIND_NORM, ATTR_KIND_INT };
} // namespace albedo

#endif // CHAOSEQUATIONS_VERTEXATTRIBUTE_H
