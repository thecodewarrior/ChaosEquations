#include <algorithm>
#include "VertexBuffer.h"

namespace albedo {
    VertexBuffer::VertexBuffer() {
        glGenBuffers(1, &vbo);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &vbo);
    }

    int VertexBuffer::reserve(int size) {
        int offset = stride;
        stride += size;
        return offset;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }

    void VertexBuffer::end_vertex() {
        index++;
        if(index * stride >= data.size()) {
            data.resize(buffer_size(index + 1));
        }
        vertex = &data[index * stride];
    }

    void VertexBuffer::clear() {
        index = 0;
        if(data.empty()) {
            data.resize(buffer_size(1));
        }
        vertex = &data[0];
    }

    void VertexBuffer::upload() {
        bind();
        glBufferData(GL_ARRAY_BUFFER, buffer_size(index), data.data(), GL_DYNAMIC_DRAW);
    }

    // https://stackoverflow.com/a/365068/1541907
    inline size_t pow2roundup(size_t x) {
        if(x == 0)
            return 0;
        --x;
        x |= x >> 1u;
        x |= x >> 2u;
        x |= x >> 4u;
        x |= x >> 8u;
        x |= x >> 16u;
        x |= x >> 32u;
        return x + 1u;
    }

    size_t VertexBuffer::buffer_size(size_t vertex_count) const {
        return stride * std::max(pow2roundup(vertex_count), 64ul);
    }
}