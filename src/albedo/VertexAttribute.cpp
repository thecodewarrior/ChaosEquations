#include <albedo/VertexAttribute.h>

namespace albedo {
VertexAttributeBase::VertexAttributeBase(const std::shared_ptr<VertexBuffer> &buffer, std::string name, int size)
    : buffer(buffer), name(std::move(name)), size(size), offset(buffer->reserve(size)) {}
} // namespace albedo