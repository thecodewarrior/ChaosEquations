// This intentionally has no header guard. It's included multiple times with different defines in vertex_attributes.h
// ATTR_GL_TYPE and ATTR_TYPE are undefined at the end of this file so they can be redefined without warnings
// The vector input types and ATTR_IS_INT are *not* undefined, since they tend to carry through

// input macros:
// ATTR_GL_TYPE - the GL type (e.g. GL_FLOAT)
// ATTR_TYPE - the C++ type (e.g. GLfloat)
// ATTR_VEC2_TYPE - the GLM vec2 type, if it exists
// ATTR_VEC3_TYPE - the GLM vec3 type, if it exists
// ATTR_VEC4_TYPE - the GLM vec4 type, if it exists
// ATTR_IS_INT - if defined, include a attribute kind parameter

#include "../common_gl.h"
#include "VertexAttribute.h"

// to appease the code highlighting gods
#ifndef ATTR_GL_TYPE
#define ATTR_GL_TYPE 0
#define ATTR_TYPE char
#endif

namespace albedo {
#ifdef ATTR_IS_INT
#define ATTR_IMPL(count) \
        public: \
        IntAttributeKind kind; \
        VertexAttribute(const std::shared_ptr<VertexBuffer> &buffer, GLuint attribute, IntAttributeKind kind) \
                : VertexAttributeBase(buffer, attribute, sizeof(ATTR_TYPE) * count), kind(kind) {} \
        void setup_attrib_pointer() const override { \
            switch(kind) { \
                case ATTR_KIND_FLOAT: \
                    glVertexAttribPointer(index, size, ATTR_GL_TYPE, GL_FALSE, \
                                          buffer->stride, (GLvoid *) offset); \
                case ATTR_KIND_NORM: \
                    glVertexAttribPointer(index, size, ATTR_GL_TYPE, GL_TRUE, \
                                          buffer->stride, (GLvoid *) offset); \
                case ATTR_KIND_INT: \
                    glVertexAttribIPointer(index, count, ATTR_GL_TYPE, \
                                           buffer->stride, (GLvoid *) offset); \
            } \
        } \
        private: \
        template<typename T> \
        ATTR_TYPE *ptr() const { \
            return reinterpret_cast<ATTR_TYPE *>(buffer->vertex + this->offset); \
        } \
        public:
#else
#define ATTR_IMPL(count) \
        public: \
        VertexAttribute(const std::shared_ptr<VertexBuffer> &buffer, GLuint attribute) \
                : VertexAttributeBase(buffer, attribute, sizeof(ATTR_TYPE) * count) {} \
        void setup_attrib_pointer() const override { \
            glVertexAttribPointer(index, count, ATTR_GL_TYPE, GL_FALSE, \
                                  buffer->stride, (GLvoid *) offset); \
        } \
        private: \
        template<typename T> \
        ATTR_TYPE *ptr() const { \
            return reinterpret_cast<ATTR_TYPE *>(buffer->vertex + this->offset); \
        } \
        public:
#endif

    template<>
    class VertexAttribute<ATTR_GL_TYPE, 1> : public VertexAttributeBase {
        ATTR_IMPL(1)

        void set(ATTR_TYPE value) const {
            ptr<ATTR_TYPE>()[0] = value;
        }
    };

    template<>
    class VertexAttribute<ATTR_GL_TYPE, 2> : public VertexAttributeBase {
        ATTR_IMPL(2)

        void set(ATTR_TYPE x, ATTR_TYPE y) const {
            auto p = ptr<ATTR_TYPE>();
            p[0] = x;
            p[1] = y;
        }

#ifdef ATTR_VEC2_TYPE
        void set(ATTR_VEC2_TYPE value) const {
            set(value.x, value.y);
        }
#endif
    };

    template<>
    class VertexAttribute<ATTR_GL_TYPE, 3> : public VertexAttributeBase {
        ATTR_IMPL(3)

        void set(ATTR_TYPE x, ATTR_TYPE y, ATTR_TYPE z) const {
            auto p = ptr<ATTR_TYPE>();
            p[0] = x;
            p[1] = y;
            p[2] = z;
        }

#ifdef ATTR_VEC3_TYPE
        void set(ATTR_VEC3_TYPE value) const {
            set(value.x, value.y, value.z);
        }
#endif
    };

    template<>
    class VertexAttribute<ATTR_GL_TYPE, 4> : public VertexAttributeBase {
        ATTR_IMPL(4)

        void set(ATTR_TYPE x, ATTR_TYPE y, ATTR_TYPE z, ATTR_TYPE w) const {
            auto p = ptr<ATTR_TYPE>();
            p[0] = x;
            p[1] = y;
            p[2] = z;
            p[3] = w;
        }

#ifdef ATTR_VEC4_TYPE
        void set(ATTR_VEC4_TYPE value) const {
            set(value.x, value.y, value.z, value.w);
        }
#endif
    };
}

#undef ATTR_IMPL

// undefine inputs to be explicitly redefined next time
#undef ATTR_GL_TYPE
#undef ATTR_TYPE
