#ifndef CHAOSEQUATIONS_UNIFORMS_H
#define CHAOSEQUATIONS_UNIFORMS_H

#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../common_gl.h"
#include "Uniform.h"
#include "uniform_type.h"

#ifndef GLSL_VERSION
#define GLSL_VERSION 420
#endif

#define ALBEDO_UNIFORM_VALUE_IMPL(glsl_type, value_type, gl_impl) \
    template <> class Uniform<glsl_type> : public UniformBase { \
    public: \
        explicit Uniform(const std::string &name) : UniformBase(name) {} \
\
    private: \
        value_type value{}; \
\
    public: \
        template <typename... Args> void set(Args &&...args) { value = value_type(std::forward<Args>(args)...); } \
\
    protected: \
        void impl(TextureUnitAllocator &tex_units) const override gl_impl \
    };
//    void Uniform<glsl_type>::impl(TextureUnitAllocator &tex_units) const

#define ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_type, target) \
    template <> class Uniform<glsl_type> : public UniformBase { \
    public: \
        explicit Uniform(const std::string &name) : UniformBase(name) {} \
\
    private: \
        GLuint value{}; \
\
    public: \
        void bind(GLuint texture) { value = texture; } \
\
    protected: \
        void impl(TextureUnitAllocator &tex_units) const override { \
            glUniform1i(location, tex_units.reserve(target, value)); \
        } \
    };

namespace albedo {
#if GLSL_VERSION >= 110

ALBEDO_UNIFORM_VALUE_IMPL(glsl_float, float, { glUniform1f(location, value); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_vec2, glm::vec2, { glUniform2f(location, value.x, value.y); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_vec3, glm::vec3, { glUniform3f(location, value.x, value.y, value.z); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_vec4, glm::vec4, { glUniform4f(location, value.x, value.y, value.z, value.w); })

ALBEDO_UNIFORM_VALUE_IMPL(glsl_bool, bool, { glUniform1i(location, value); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_bvec2, glm::bvec2, { glUniform2i(location, value.x, value.y); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_bvec3, glm::bvec3, { glUniform3i(location, value.x, value.y, value.z); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_bvec4, glm::bvec4, { glUniform4i(location, value.x, value.y, value.z, value.w); })

ALBEDO_UNIFORM_VALUE_IMPL(glsl_int, GLint, { glUniform1i(location, value); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_ivec2, glm::ivec2, { glUniform2i(location, value.x, value.y); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_ivec3, glm::ivec3, { glUniform3i(location, value.x, value.y, value.z); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_ivec4, glm::ivec4, { glUniform4i(location, value.x, value.y, value.z, value.w); })

ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat2, glm::mat2x2, { glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat3, glm::mat3x3, { glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat4, glm::mat4x4, { glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]); })

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler1D, GL_TEXTURE_1D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2D, GL_TEXTURE_2D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler3D, GL_TEXTURE_3D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_samplerCube, GL_TEXTURE_CUBE_MAP)

#endif

/* GLSL 1.20 - OpenGL 2.1
    + mat2x3, mat2x4, mat3x2, mat3x4, mat4x2, mat4x3
*/
#if GLSL_VERSION >= 120
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat2x3, glm::mat2x3, { glUniformMatrix2x3fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat2x4, glm::mat2x4, { glUniformMatrix2x4fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat3x2, glm::mat3x2, { glUniformMatrix3x2fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat3x4, glm::mat3x4, { glUniformMatrix3x4fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat4x2, glm::mat4x2, { glUniformMatrix4x2fv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_mat4x3, glm::mat4x3, { glUniformMatrix4x3fv(location, 1, GL_FALSE, &value[0][0]); })
#endif

/* GLSL 1.30 - OpenGL 3.0
    + uint, uvec2, uvec3, uvec4
    + sampler1DArray, sampler2DArray, sampler1DArrayShadow, sampler2DArrayShadow
    + isampler1D, isampler2D, isampler3D, isamplerCube, isampler1DArray, isampler2DArray
    + usampler1D, usampler2D, usampler3D, usamplerCube, usampler1DArray, usampler2DArray
*/
#if GLSL_VERSION >= 130
ALBEDO_UNIFORM_VALUE_IMPL(glsl_uint, GLuint, { glUniform1ui(location, value); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_uvec2, glm::uvec2, { glUniform2ui(location, value.x, value.y); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_uvec3, glm::uvec3, { glUniform3ui(location, value.x, value.y, value.z); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_uvec4, glm::uvec4, { glUniform4ui(location, value.x, value.y, value.z, value.w); })

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler1DArray, GL_TEXTURE_1D_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DArray, GL_TEXTURE_2D_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler1DArrayShadow, GL_TEXTURE_1D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DArrayShadow, GL_TEXTURE_2D)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler1D, GL_TEXTURE_1D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler2D, GL_TEXTURE_2D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler3D, GL_TEXTURE_3D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isamplerCube, GL_TEXTURE_CUBE_MAP)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler1DArray, GL_TEXTURE_1D_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler2DArray, GL_TEXTURE_2D_ARRAY)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler1D, GL_TEXTURE_1D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler2D, GL_TEXTURE_2D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler3D, GL_TEXTURE_3D)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usamplerCube, GL_TEXTURE_CUBE_MAP)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler1DArray, GL_TEXTURE_1D_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler2DArray, GL_TEXTURE_2D_ARRAY)

#endif

/* GLSL 1.40 - OpenGL 3.1
    + sampler2DRect, sampler2DRectShadow, samplerBuffer
    + isampler2DRect, isamplerBuffer
    + usampler2DRect, usamplerBuffer
*/
#if GLSL_VERSION >= 140
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DRect, GL_TEXTURE_RECTANGLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DRectShadow, GL_TEXTURE_RECTANGLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_samplerBuffer, GL_TEXTURE_BUFFER)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler2DRect, GL_TEXTURE_RECTANGLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isamplerBuffer, GL_TEXTURE_BUFFER)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler2DRect, GL_TEXTURE_RECTANGLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usamplerBuffer, GL_TEXTURE_BUFFER)
#endif

/* GLSL 1.50 - OpenGL 3.2
    + sampler2DMS, sampler2DMSArray
    + isampler2DMS, isampler2DMSArray
    + usampler2DMS, usampler2DMSArray
*/
#if GLSL_VERSION >= 150
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DMS, GL_TEXTURE_2D_MULTISAMPLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_sampler2DMSArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler2DMS, GL_TEXTURE_2D_MULTISAMPLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isampler2DMSArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler2DMS, GL_TEXTURE_2D_MULTISAMPLE)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usampler2DMSArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
#endif

/* GLSL 4.00 - OpenGL 4.0
    + double, dvec2, dvec3, dvec4
    + dmat2, dmat3, dmat4, dmat2x3, dmat2x4, dmat3x2, dmat3x4, dmat4x2, dmat4x3
    + samplerCubeShadow, samplerCubeArray, samplerCubeArrayShadow
    + isamplerCubeArray
    + usamplerCubeArray
*/
#if GLSL_VERSION >= 400

ALBEDO_UNIFORM_VALUE_IMPL(glsl_double, double, { glUniform1d(location, value); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dvec2, glm::dvec2, { glUniform2d(location, value.x, value.y); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dvec3, glm::dvec3, { glUniform3d(location, value.x, value.y, value.z); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dvec4, glm::dvec4, { glUniform4d(location, value.x, value.y, value.z, value.w); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat2, glm::dmat2x2, { glUniformMatrix2dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat3, glm::dmat3x3, { glUniformMatrix3dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat4, glm::dmat4x4, { glUniformMatrix4dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat2x3, glm::dmat2x3, { glUniformMatrix2x3dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat2x4, glm::dmat2x4, { glUniformMatrix2x4dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat3x2, glm::dmat3x2, { glUniformMatrix3x2dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat3x4, glm::dmat3x4, { glUniformMatrix3x4dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat4x2, glm::dmat4x2, { glUniformMatrix4x2dv(location, 1, GL_FALSE, &value[0][0]); })
ALBEDO_UNIFORM_VALUE_IMPL(glsl_dmat4x3, glm::dmat4x3, { glUniformMatrix4x3dv(location, 1, GL_FALSE, &value[0][0]); })

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_samplerCubeShadow, GL_TEXTURE_CUBE_MAP)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_samplerCubeArray, GL_TEXTURE_CUBE_MAP_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_samplerCubeArrayShadow, GL_TEXTURE_CUBE_MAP_ARRAY)

ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_isamplerCubeArray, GL_TEXTURE_CUBE_MAP_ARRAY)
ALBEDO_UNIFORM_SAMPLER_IMPL(glsl_usamplerCubeArray, GL_TEXTURE_CUBE_MAP_ARRAY)

#endif

/* GLSL 4.20 - OpenGL 4.2
    + atomic_uint
    + image1D, image2D, image3D, imageCube, image2DRect, image1DArray, image2DArray, imageBuffer, image2DMS,
   image2DMSArray
    + iimage1D, iimage2D, iimage3D, iimageCube, iimage2DRect, iimage1DArray, iimage2DArray, iimageBuffer, iimage2DMS,
   iimage2DMSArray
    + uimage1D, uimage2D, uimage3D, uimageCube, uimage2DRect, uimage1DArray, uimage2DArray, uimageBuffer, uimage2DMS,
   uimage2DMSArray
 */
#if GLSL_VERSION >= 420
#endif
} // namespace albedo

#undef ALBEDO_UNIFORM_VALUE_IMPL
#undef ALBEDO_UNIFORM_SAMPLER_IMPL

#endif // CHAOSEQUATIONS_UNIFORMS_H
