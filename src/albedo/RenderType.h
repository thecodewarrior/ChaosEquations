#ifndef CHAOSEQUATIONS_RENDERTYPE_H
#define CHAOSEQUATIONS_RENDERTYPE_H

#include <memory>
#include <vector>
#include <set>
#include "Shader.h"
#include "VertexBuffer.h"
#include "vertex_attributes.h"

namespace albedo {
    class RenderType {
    public:
        GLuint vao;
        std::shared_ptr<Shader> shader;
        std::vector<std::shared_ptr<VertexAttributeBase>> attributes;
        std::set<std::shared_ptr<VertexBuffer>> buffers;
        size_t vertex_count = 0;

        explicit RenderType(std::shared_ptr<Shader> shader);
        ~RenderType();

        void end_vertex();
        void draw(GLenum type);

    protected:
        template<GLenum T, int C, typename... Args>
        std::shared_ptr<VertexAttribute<T, C>> make_attribute(
                Args&&... args
        ) {
            auto attribute = std::make_shared<VertexAttribute<T, C>>(std::forward<Args>(args)...);
            std::shared_ptr<VertexAttributeBase> base = attribute;
            attributes.push_back(base);
            buffers.insert(base->buffer);
            return attribute;
        }

        void setup_vao() const;
    };

    /**
     * Creates a method with the supplied <code>name</code> that sets the value of the specified <code>attr</code> field
     * and returns a reference to this instance.
     */
#define RENDER_TYPE_BUILDER(self, name, attr) \
    template<typename... Args> \
    self &name(Args&&... args) { \
        attr->set(std::forward<Args>(args)...); \
        return *this; \
    }
}

#endif //CHAOSEQUATIONS_RENDERTYPE_H
