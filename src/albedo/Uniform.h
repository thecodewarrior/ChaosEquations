#ifndef CHAOSEQUATIONS_UNIFORM_H
#define CHAOSEQUATIONS_UNIFORM_H

#include "../common_gl.h"
#include "uniform_type.h"
#include <map>
#include <string>

namespace albedo {

/// A utility class that dynamically allocates texture units
class TextureUnitAllocator {
public:
    GLuint reserve(GLenum target, GLuint texture);
    void bind();
    void unbind();

private:
    struct BindInfo {
        GLenum target;
        GLuint texture;

        bool operator<(const BindInfo &other) const {
            if (target == other.target) {
                return texture < other.texture;
            }
            return target < other.target;
        }
    };

    std::map<BindInfo, GLuint> texture_units;
    GLuint next_unit = 0;
};

class UniformBase {
public:
    GLint location = -1;
    std::string name;

    explicit UniformBase(std::string name) : name(std::move(name)) {}

    void push(TextureUnitAllocator &tex_units) const {
        if (location >= 0)
            impl(tex_units);
    }

    /// the texture ID to reserve. The resulting texture unit will be in
    [[nodiscard]] virtual GLuint tex_id() const { return 0; }

protected:
    virtual void impl(TextureUnitAllocator &tex_units) const {}
};

template <uniform_type T> class Uniform {};

template <uniform_type T> class UniformArray {};

} // namespace albedo

#endif // CHAOSEQUATIONS_UNIFORM_H
