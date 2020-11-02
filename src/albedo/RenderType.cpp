#include "RenderType.h"

#include <utility>

namespace albedo {
    RenderType::RenderType(std::shared_ptr<Shader> shader) : shader(std::move(shader)), vao(0) {
        glGenVertexArrays(1, &vao);
    }
    RenderType::~RenderType() {
        glDeleteVertexArrays(1, &vao);
    }

    void RenderType::setup_vao() const {
        glBindVertexArray(vao);
        for(auto &attribute : attributes) {
            attribute->setup_vao();
        }
        for(auto &buffer : buffers) {
            buffer->clear(); // ensures the first vertex is allocated
        }
    }

    void RenderType::end_vertex() {
        vertex_count++;
        for(auto &buffer : buffers) {
            buffer->end_vertex();
        }
    }

    void RenderType::draw(GLenum type) {
        if(vertex_count == 0)
            return;

        glUseProgram(shader->program);
        glBindVertexArray(vao);
        for(auto &buffer : buffers) {
            buffer->upload();
        }

        glDrawArrays(type, 0, vertex_count);

        vertex_count = 0;
        for(auto &buffer : buffers) {
            buffer->clear();
        }
    }
}
