#ifndef CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H
#define CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "VertexAttribute.h"

#define ALBEDO_ATTRIBUTE_BEGIN(gl_type, attr_type, components) \
    template <> class VertexAttribute<gl_type, components> : public VertexAttributeBase { \
    public: \
        VertexAttribute(const std::shared_ptr<VertexBuffer> &buffer, std::string name) \
            : VertexAttributeBase(buffer, std::move(name), sizeof(attr_type) * components) {} \
        void setup_attrib_pointer() const override { \
            glVertexAttribPointer(location, components, gl_type, GL_FALSE, buffer->stride, (GLvoid *)offset); \
        } \
\
    private: \
        attr_type *ptr() const { return reinterpret_cast<attr_type *>(buffer->vertex + this->offset); } \
\
    public:

#define ALBEDO_ATTRIBUTE_INT_BEGIN(gl_type, attr_type, components) \
    template <> class VertexAttribute<gl_type, components> : public VertexAttributeBase { \
        IntAttributeKind kind; \
\
    public: \
        VertexAttribute(const std::shared_ptr<VertexBuffer> &buffer, std::string name, IntAttributeKind kind) \
            : VertexAttributeBase(buffer, std::move(name), sizeof(attr_type) * components), kind(kind) {} \
        void setup_attrib_pointer() const override { \
            switch (kind) { \
            case ATTR_KIND_FLOAT: \
                glVertexAttribPointer(location, components, gl_type, GL_FALSE, buffer->stride, (GLvoid *)offset); \
            case ATTR_KIND_NORM: \
                glVertexAttribPointer(location, components, gl_type, GL_TRUE, buffer->stride, (GLvoid *)offset); \
            case ATTR_KIND_INT: \
                glVertexAttribIPointer(location, components, gl_type, buffer->stride, (GLvoid *)offset); \
            } \
        } \
\
    private: \
        attr_type *ptr() const { return reinterpret_cast<attr_type *>(buffer->vertex + this->offset); } \
\
    public:

#define ALBEDO_ATTRIBUTE_SETTER_1(attr_type) \
    void set(attr_type x) const { \
        auto p = ptr(); \
        p[0] = x; \
    }

#define ALBEDO_ATTRIBUTE_SETTER_2(attr_type) \
    void set(attr_type x, attr_type y) const { \
        auto p = ptr(); \
        p[0] = x; \
        p[1] = y; \
    }

#define ALBEDO_ATTRIBUTE_SETTER_GLM_2(vec_type) \
    void set(vec_type value) const { set(value.x, value.y); }

#define ALBEDO_ATTRIBUTE_SETTER_3(attr_type) \
    void set(attr_type x, attr_type y, attr_type z) const { \
        auto p = ptr(); \
        p[0] = x; \
        p[1] = y; \
        p[2] = z; \
    }

#define ALBEDO_ATTRIBUTE_SETTER_GLM_3(vec_type) \
    void set(vec_type value) const { set(value.x, value.y, value.z); }

#define ALBEDO_ATTRIBUTE_SETTER_4(attr_type) \
    void set(attr_type x, attr_type y, attr_type z, attr_type w) const { \
        auto p = ptr(); \
        p[0] = x; \
        p[1] = y; \
        p[2] = z; \
        p[3] = w; \
    }

#define ALBEDO_ATTRIBUTE_SETTER_GLM_4(vec_type) \
    void set(vec_type value) const { set(value.x, value.y, value.z, value.w); }

#define ALBEDO_ATTRIBUTE_END \
    } \
    ;


namespace albedo {

// === floats ===
ALBEDO_ATTRIBUTE_BEGIN(GL_HALF_FLOAT, GLhalf, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLhalf)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_HALF_FLOAT, GLhalf, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLhalf)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_HALF_FLOAT, GLhalf, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLhalf)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_HALF_FLOAT, GLhalf, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLhalf)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_BEGIN(GL_FLOAT, GLfloat, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLfloat)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FLOAT, GLfloat, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLfloat)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FLOAT, GLfloat, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLfloat)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FLOAT, GLfloat, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLfloat)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_BEGIN(GL_FIXED, GLfixed, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLfixed)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FIXED, GLfixed, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLfixed)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FIXED, GLfixed, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLfixed)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_BEGIN(GL_FIXED, GLfixed, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLfixed)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

// === signed integers ===
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_BYTE, GLbyte, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLbyte)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_BYTE, GLbyte, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLbyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_BYTE, GLbyte, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLbyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_BYTE, GLbyte, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLbyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_INT_BEGIN(GL_SHORT, GLshort, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLshort)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_SHORT, GLshort, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLshort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_SHORT, GLshort, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLshort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_SHORT, GLshort, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLshort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_INT_BEGIN(GL_INT, GLint, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLint)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_INT, GLint, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::vec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_INT, GLint, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::vec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_INT, GLint, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::vec4)
ALBEDO_ATTRIBUTE_END

// === unsigned integers ===
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_BYTE, GLubyte, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLubyte)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_BYTE, GLubyte, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLubyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::uvec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_BYTE, GLubyte, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLubyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::uvec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_BYTE, GLubyte, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLubyte)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::uvec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_SHORT, GLushort, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLushort)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_SHORT, GLushort, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLushort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::uvec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_SHORT, GLushort, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLushort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::uvec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_SHORT, GLushort, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLushort)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::uvec4)
ALBEDO_ATTRIBUTE_END

ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_INT, GLuint, 1)
    ALBEDO_ATTRIBUTE_SETTER_1(GLuint)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_INT, GLuint, 2)
    ALBEDO_ATTRIBUTE_SETTER_2(GLuint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_2(glm::uvec2)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_INT, GLuint, 3)
    ALBEDO_ATTRIBUTE_SETTER_3(GLuint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_3(glm::uvec3)
ALBEDO_ATTRIBUTE_END
ALBEDO_ATTRIBUTE_INT_BEGIN(GL_UNSIGNED_INT, GLuint, 4)
    ALBEDO_ATTRIBUTE_SETTER_4(GLuint)
    ALBEDO_ATTRIBUTE_SETTER_GLM_4(glm::uvec4)
ALBEDO_ATTRIBUTE_END

}

#undef ALBEDO_ATTRIBUTE_BEGIN
#undef ALBEDO_ATTRIBUTE_INT_BEGIN
#undef ALBEDO_ATTRIBUTE_SETTER_1
#undef ALBEDO_ATTRIBUTE_SETTER_2
#undef ALBEDO_ATTRIBUTE_SETTER_GLM_2
#undef ALBEDO_ATTRIBUTE_SETTER_3
#undef ALBEDO_ATTRIBUTE_SETTER_GLM_3
#undef ALBEDO_ATTRIBUTE_SETTER_4
#undef ALBEDO_ATTRIBUTE_SETTER_GLM_4
#undef ALBEDO_ATTRIBUTE_END

#endif //CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H
