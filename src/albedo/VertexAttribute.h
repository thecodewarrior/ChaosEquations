#ifndef CHAOSEQUATIONS_VERTEXATTRIBUTE_H
#define CHAOSEQUATIONS_VERTEXATTRIBUTE_H

#include <memory>
#include "VertexBuffer.h"

namespace albedo {
    class VertexAttributeBase {
    public:
        const GLuint index;
        const std::shared_ptr<VertexBuffer> buffer;
        const size_t size;
        const size_t offset;

        VertexAttributeBase(
                const std::shared_ptr<VertexBuffer> &buffer,
                GLuint index, int size
        );

        void setup_vao() const {
            buffer->bind();
            setup_attrib_pointer();
            glEnableVertexAttribArray(index);
        }

    protected:
        virtual void setup_attrib_pointer() const {}
    };

    template<GLenum G, int C>
    class VertexAttribute {};

    enum IntAttributeKind {
        ATTR_KIND_FLOAT,
        ATTR_KIND_NORM,
        ATTR_KIND_INT
    };
}

#endif //CHAOSEQUATIONS_VERTEXATTRIBUTE_H
