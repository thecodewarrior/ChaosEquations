#include "VertexAttribute.h"

namespace albedo {
    VertexAttributeBase::VertexAttributeBase(
            const std::shared_ptr<VertexBuffer> &buffer,
            GLuint index, int size
    ) : buffer(buffer), index(index), size(size), offset(buffer->reserve(size)) {
    }
}