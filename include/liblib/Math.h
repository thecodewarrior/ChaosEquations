#ifndef CHAOSEQUATIONS_MATH_H
#define CHAOSEQUATIONS_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ll {

// region 4x4 matrix transforms (which just forward to glm)
/// Builds an identity matrix.
template <typename genType> inline constexpr genType identity() { return glm::identity<genType>(); }

/// Builds a translation 4 * 4 matrix created from a vector of 3 components.
///
/// @param m Input matrix multiplied by this translation matrix.
/// @param v Coordinates of a translation vector.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
///
/// @code
/// #include <liblib/Math.h>
/// ...
/// glm::mat4 m = ll::translate(glm::mat4(1.0f), glm::vec3(1.0f));
/// // m[0][0] == 1.0f, m[0][1] == 0.0f, m[0][2] == 0.0f, m[0][3] == 0.0f
/// // m[1][0] == 0.0f, m[1][1] == 1.0f, m[1][2] == 0.0f, m[1][3] == 0.0f
/// // m[2][0] == 0.0f, m[2][1] == 0.0f, m[2][2] == 1.0f, m[2][3] == 0.0f
/// // m[3][0] == 1.0f, m[3][1] == 1.0f, m[3][2] == 1.0f, m[3][3] == 1.0f
/// @endcode
///
/// @see - translate(mat<4, 4, T, Q> const& m, T x, T y, T z)
/// @see - translate(vec<3, T, Q> const& v)
/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml">glTranslate man page</a>
template <typename T, glm::qualifier Q>
inline glm::mat<4, 4, T, Q> translate(glm::mat<4, 4, T, Q> const &m, glm::vec<3, T, Q> const &v) {
    return glm::translate<T, Q>(m, v);
}

/// Builds a rotation 4 * 4 matrix created from an axis vector and an angle.
///
/// @param m Input matrix multiplied by this rotation matrix.
/// @param angle Rotation angle expressed in radians.
/// @param axis Rotation axis, recommended to be normalized.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
///
/// @see - rotate(mat<4, 4, T, Q> const& m, T angle, T x, T y, T z)
/// @see - rotate(T angle, vec<3, T, Q> const& v)
/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml">glRotate man page</a>
template <typename T, glm::qualifier Q>
inline glm::mat<4, 4, T, Q> rotate(glm::mat<4, 4, T, Q> const &m, T angle, glm::vec<3, T, Q> const &axis) {
    return glm::rotate<T, Q>(m, angle, axis);
}

/// Builds a scale 4 * 4 matrix created from 3 scalars.
///
/// @param m Input matrix multiplied by this scale matrix.
/// @param v Ratio of scaling for each axis.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
///
/// @see - scale(mat<4, 4, T, Q> const& m, T x, T y, T z)
/// @see - scale(vec<3, T, Q> const& v)
/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glScale.xml">glScale man page</a>
template <typename T, glm::qualifier Q>
inline glm::mat<4, 4, T, Q> scale(glm::mat<4, 4, T, Q> const &m, glm::vec<3, T, Q> const &v) {
    return glm::scale<T, Q>(m, v);
}
// endregion

// region 3x3 matrix transforms
/// Builds a translation 3 * 3 matrix created from a vector of 2 components.
///
/// @param m Input matrix multiplied by this translation matrix.
/// @param v Coordinates of a translation vector.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
///
/// @code
/// #include <liblib/Math.h>
/// ...
/// glm::mat3 m = ll::translate(glm::mat3(1.0f), glm::vec2(1.0f));
/// // m[0][0] == 1.0f, m[0][1] == 0.0f, m[0][2] == 0.0f
/// // m[1][0] == 0.0f, m[1][1] == 1.0f, m[1][2] == 0.0f
/// // m[2][0] == 1.0f, m[2][1] == 1.0f, m[2][2] == 1.0f
/// @endcode
template <typename T, glm::qualifier Q>
inline glm::mat<3, 3, T, Q> translate(glm::mat<3, 3, T, Q> const &m, glm::vec<2, T, Q> const &v) {
    glm::mat<3, 3, T, Q> result(m);
    result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
    return result;
}

/// Builds a rotation 3 * 3 matrix created from an angle.
///
/// @param m Input matrix multiplied by this rotation matrix.
/// @param angle Rotation angle expressed in radians.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
///
/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml">glRotate man page</a>
template <typename T, glm::qualifier Q> inline glm::mat<3, 3, T, Q> rotate(glm::mat<3, 3, T, Q> const &m, T angle) {
    T const a = angle;
    T const c = cos(a);
    T const s = sin(a);

    glm::mat<3, 3, T, Q> result;
    result[0] = m[0] * c + m[1] * s;
    result[1] = m[0] * -s + m[1] * c;
    result[2] = m[2];
    return result;
}

/// Builds a scale 3 * 3 matrix created from 2 scalars.
///
/// @param m Input matrix multiplied by this scale matrix.
/// @param v Ratio of scaling for each axis.
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
template <typename T, glm::qualifier Q>
inline glm::mat<3, 3, T, Q> scale(glm::mat<3, 3, T, Q> const &m, glm::vec<2, T, Q> const &v) {
    glm::mat<3, 3, T, Q> result;
    result[0] = m[0] * v[0];
    result[1] = m[1] * v[1];
    result[2] = m[2];
    return result;
}
// endregion

/// Extends a 3x3 (XY) transformation matrix into a 4x4 (XYZ) transformation matrix
///
/// @param m Matrix to convert
///
/// @tparam T A floating-point scalar type
/// @tparam Q A value from qualifier enum
template <typename T, glm::qualifier Q> inline glm::mat<4, 4, T, Q> extend_transform(glm::mat<3, 3, T, Q> const &m) {
    return {{m[0][0], m[0][1], 0, 0}, {m[1][0], m[1][1], 0, 0}, {0, 0, 1, 0}, {m[2][0], m[2][1], 0, 1}};
}

} // namespace ll

#endif // CHAOSEQUATIONS_MATH_H
