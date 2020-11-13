#ifndef CHAOSEQUATIONS_UNIFORM_TYPE_H
#define CHAOSEQUATIONS_UNIFORM_TYPE_H

#ifndef GLSL_VERSION
#define GLSL_VERSION 420
#endif

namespace albedo {

// clang-format off
enum uniform_type {
#if GLSL_VERSION >= 110
    /* GLSL 1.10 - OpenGL 2.0 */
    glsl_float = 0, glsl_vec2, glsl_vec3, glsl_vec4,
    glsl_bool, glsl_bvec2, glsl_bvec3, glsl_bvec4,
    glsl_int, glsl_ivec2, glsl_ivec3, glsl_ivec4,
    glsl_mat2, glsl_mat3, glsl_mat4,
    glsl_sampler1D, glsl_sampler2D, glsl_sampler3D, glsl_samplerCube,
#endif

#if GLSL_VERSION >= 120
    /* GLSL 1.20 - OpenGL 2.1 */
    glsl_mat2x3 = 19, glsl_mat2x4,
    glsl_mat3x2, glsl_mat3x4,
    glsl_mat4x2, glsl_mat4x3,
#endif

#if GLSL_VERSION >= 130
    /* GLSL 1.30 - OpenGL 3.0 */
    glsl_uint = 25, glsl_uvec2, glsl_uvec3, glsl_uvec4,
    glsl_sampler1DArray, glsl_sampler2DArray, glsl_sampler1DArrayShadow, glsl_sampler2DArrayShadow,
    glsl_isampler1D, glsl_isampler2D, glsl_isampler3D, glsl_isamplerCube, glsl_isampler1DArray, glsl_isampler2DArray,
    glsl_usampler1D, glsl_usampler2D, glsl_usampler3D, glsl_usamplerCube, glsl_usampler1DArray, glsl_usampler2DArray,
#endif

#if GLSL_VERSION >= 140
    /* GLSL 1.40 - OpenGL 3.1 */
    glsl_sampler2DRect = 45, glsl_sampler2DRectShadow, glsl_samplerBuffer,
    glsl_isampler2DRect, glsl_isamplerBuffer,
    glsl_usampler2DRect, glsl_usamplerBuffer,
#endif

#if GLSL_VERSION >= 150
    /* GLSL 1.50 - OpenGL 3.2 */
    glsl_sampler2DMS = 52, glsl_sampler2DMSArray,
    glsl_isampler2DMS, glsl_isampler2DMSArray,
    glsl_usampler2DMS, glsl_usampler2DMSArray,
#endif

#if GLSL_VERSION >= 400
    /* GLSL 4.00 - OpenGL 4.0 */
    glsl_double = 58, glsl_dvec2, glsl_dvec3, glsl_dvec4,
    glsl_dmat2, glsl_dmat3, glsl_dmat4, glsl_dmat2x3, glsl_dmat2x4, glsl_dmat3x2, glsl_dmat3x4, glsl_dmat4x2, glsl_dmat4x3,
    glsl_samplerCubeShadow, glsl_samplerCubeArray, glsl_samplerCubeArrayShadow,
    glsl_isamplerCubeArray,
    glsl_usamplerCubeArray,
#endif

#if GLSL_VERSION >= 420
    /* GLSL 4.20 - OpenGL 4.2 */
    glsl_atomic_uint = 76,
    glsl_image1D, glsl_image2D, glsl_image3D, glsl_imageCube, glsl_image2DRect,
    glsl_image1DArray, glsl_image2DArray, glsl_imageBuffer, glsl_image2DMS, glsl_image2DMSArray,
    glsl_iimage1D, glsl_iimage2D, glsl_iimage3D, glsl_iimageCube, glsl_iimage2DRect,
    glsl_iimage1DArray, glsl_iimage2DArray, glsl_iimageBuffer, glsl_iimage2DMS, glsl_iimage2DMSArray,
    glsl_uimage1D, glsl_uimage2D, glsl_uimage3D, glsl_uimageCube, glsl_uimage2DRect,
    glsl_uimage1DArray, glsl_uimage2DArray, glsl_uimageBuffer, glsl_uimage2DMS, glsl_uimage2DMSArray,
#endif
};
// clang-format on

} // namespace albedo

#endif // CHAOSEQUATIONS_UNIFORM_TYPE_H
