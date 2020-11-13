#include "RenderBuffer.h"

#include <utility>

namespace albedo {
RenderBuffer::RenderBuffer(std::shared_ptr<Shader> shader) : shader(std::move(shader)), vao(0) {
    glGenVertexArrays(1, &vao);
}
RenderBuffer::~RenderBuffer() { glDeleteVertexArrays(1, &vao); }

void RenderBuffer::setup() const {
    glBindVertexArray(vao);
    for (auto &attribute : attributes) {
        attribute->location = shader->attribute_location(attribute->name);
        attribute->setup_vao();
    }
    for (auto &buffer : buffers) {
        buffer->clear(); // ensures the first vertex is allocated
    }
    for (auto &uniform : uniforms) {
        uniform->location = shader->uniform_location(uniform->name);
    }
}

void RenderBuffer::end_vertex() {
    vertex_count++;
    for (auto &buffer : buffers) {
        buffer->end_vertex();
    }
}

void RenderBuffer::draw(GLenum type) {
    if (vertex_count == 0)
        return;

    glUseProgram(shader->program);
    TextureUnitAllocator tex_units;
    for (auto &uniform : uniforms) {
        uniform->push(tex_units);
    }
    tex_units.bind();

    glBindVertexArray(vao);
    for (auto &buffer : buffers) {
        buffer->upload();
    }

    glDrawArrays(type, 0, vertex_count);

    vertex_count = 0;
    for (auto &buffer : buffers) {
        buffer->clear();
    }

    tex_units.unbind();
}
} // namespace albedo
