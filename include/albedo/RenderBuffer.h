#ifndef CHAOSEQUATIONS_RENDERBUFFER_H
#define CHAOSEQUATIONS_RENDERBUFFER_H

#include "Shader.h"
#include "VertexBuffer.h"
#include "uniforms.h"
#include "vertex_attributes.h"
#include <memory>
#include <set>
#include <vector>

namespace albedo {
class RenderBuffer {
public:
    GLuint vao;
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<VertexAttributeBase>> attributes;
    std::vector<std::shared_ptr<UniformBase>> uniforms;
    std::set<std::shared_ptr<VertexBuffer>> buffers;
    size_t vertex_count = 0;

    explicit RenderBuffer(std::shared_ptr<Shader> shader);
    ~RenderBuffer();

    void end_vertex();
    void draw(GLenum type);

protected:
    template <GLenum T, int C, typename... Args> std::shared_ptr<VertexAttribute<T, C>> make_attribute(Args &&...args) {
        auto attribute = std::make_shared<VertexAttribute<T, C>>(std::forward<Args>(args)...);
        std::shared_ptr<VertexAttributeBase> base = attribute;
        attributes.push_back(base);
        buffers.insert(base->buffer);
        return attribute;
    }

    template <uniform_type T, typename... Args> std::shared_ptr<Uniform<T>> make_uniform(Args &&...args) {
        auto attribute = std::make_shared<Uniform<T>>(std::forward<Args>(args)...);
        std::shared_ptr<UniformBase> base = attribute;
        uniforms.push_back(base);
        return attribute;
    }

    /**
     * Call this at the end of the concrete subclass's constructor. This will set up the VAO and reserve the uniforms.
     */
    void setup() const;
};

/**
 * Creates a method with the supplied <code>name</code> that sets the value of the specified <code>attr</code> field
 * and returns a reference to this instance.
 */
#define ALBEDO_BUFFER_BUILDER(self, name, attr) \
    template <typename... Args> self &name(Args &&...args) { \
        attr->set(std::forward<Args>(args)...); \
        return *this; \
    }
} // namespace albedo

#endif // CHAOSEQUATIONS_RENDERBUFFER_H
