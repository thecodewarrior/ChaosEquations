#ifndef CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H
#define CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "VertexAttribute.h"

// input macros:
// ATTR_GL_TYPE - the GL type (e.g. GL_FLOAT)
// ATTR_TYPE - the C++ type (e.g. GLfloat)
// ATTR_VEC2_TYPE - the GLM vec2 type, if it exists
// ATTR_VEC3_TYPE - the GLM vec3 type, if it exists
// ATTR_VEC4_TYPE - the GLM vec4 type, if it exists
// ATTR_IS_INT - if defined, include a attribute kind parameter

// === floats ===
#define ATTR_VEC2_TYPE glm::vec2
#define ATTR_VEC3_TYPE glm::vec3
#define ATTR_VEC4_TYPE glm::vec4
#undef  ATTR_IS_INT

#define ATTR_GL_TYPE GL_HALF_FLOAT
#define ATTR_TYPE GLhalf
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_FLOAT
#define ATTR_TYPE GLfloat
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_FIXED
#define ATTR_TYPE GLfixed
#include "VertexAttributeImpl.h"

#undef ATTR_VEC2_TYPE
#undef ATTR_VEC3_TYPE
#undef ATTR_VEC4_TYPE

// === signed integers ===
#define ATTR_VEC2_TYPE glm::ivec2
#define ATTR_VEC3_TYPE glm::ivec3
#define ATTR_VEC4_TYPE glm::ivec4
#define ATTR_IS_INT

#define ATTR_GL_TYPE GL_BYTE
#define ATTR_TYPE GLbyte
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_SHORT
#define ATTR_TYPE GLshort
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_INT
#define ATTR_TYPE GLint
#include "VertexAttributeImpl.h"

#undef ATTR_VEC2_TYPE
#undef ATTR_VEC3_TYPE
#undef ATTR_VEC4_TYPE
#undef ATTR_IS_INT

// === unsigned integers ===
#define ATTR_VEC2_TYPE glm::uvec2
#define ATTR_VEC3_TYPE glm::uvec3
#define ATTR_VEC4_TYPE glm::uvec4
#define ATTR_IS_INT

#define ATTR_GL_TYPE GL_UNSIGNED_BYTE
#define ATTR_TYPE GLubyte
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_UNSIGNED_SHORT
#define ATTR_TYPE GLushort
#include "VertexAttributeImpl.h"
#define ATTR_GL_TYPE GL_UNSIGNED_INT
#define ATTR_TYPE GLuint
#include "VertexAttributeImpl.h"

#undef ATTR_VEC2_TYPE
#undef ATTR_VEC3_TYPE
#undef ATTR_VEC4_TYPE
#undef ATTR_IS_INT

#endif //CHAOSEQUATIONS_VERTEX_ATTRIBUTES_H
