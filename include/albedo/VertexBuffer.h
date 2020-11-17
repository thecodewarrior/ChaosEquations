#ifndef CHAOSEQUATIONS_VERTEXBUFFER_H
#define CHAOSEQUATIONS_VERTEXBUFFER_H

#include "opengl.h"
#include <cstddef>
#include <vector>

namespace albedo {
class VertexBuffer {
private:
    GLuint vbo = 0;
    std::vector<char> data;

    /**
     * The index of the currently building vertex (and by extension the number of vertices already built)
     */
    size_t index = 0;

public:
    /**
     * The stride of the vertices
     */
    size_t stride = 0;

    /**
     * The currently building vertex
     */
    char *vertex;

    VertexBuffer();

    ~VertexBuffer();

    int reserve(int size);

    void bind() const;

    void end_vertex();

    void clear();

    void upload();

private:
    /**
     * The buffer size in bytes based on the given vertex count. The vertex count is rounded up to the lowest power
     * of two greater than the vertex count or 64 if the vertex count is lower than that.
     * @param vertex_count
     */
    [[nodiscard]] size_t buffer_size(size_t vertex_count) const;
};
} // namespace albedo

#endif // CHAOSEQUATIONS_VERTEXBUFFER_H
