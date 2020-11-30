#ifndef CHAOSEQUATIONS_COORDINATESPACE_H
#define CHAOSEQUATIONS_COORDINATESPACE_H

#include <exception>
#include <glm/glm.hpp>
#include <liblib/Math.h>
#include <string>
#include <vector>

namespace facade {

class CoordinateSpaceException : public std::exception {
    std::string message;

public:
    explicit CoordinateSpaceException(std::string message) : message(std::move(message)) {}
    [[nodiscard]] const char *what() const _NOEXCEPT override { return message.c_str(); }
};

template <glm::length_t d, typename T, glm::qualifier Q> class CoordinateSpace {
private:
public:
    typedef CoordinateSpace<d, T, Q> space_type;
    typedef glm::mat<d + 1, d + 1, T, Q> matrix_type;
    typedef glm::vec<d, T, Q> vector_type;
    typedef glm::vec<d + 1, T, Q> augmented_vector_type;

    /// @return The matrix taking points from this layer's coordinate space to its parent's coordinate space.
    [[nodiscard]] virtual matrix_type transform_matrix() const = 0;

    /// @return The matrix taking points from the parent's coordinate space to this layer's coordinate space.
    [[nodiscard]] virtual matrix_type inverse_transform_matrix() const = 0;

    /// Converts the passed vector from this coordinate space to its parent's coordinate space.
    ///
    /// @param v the vector to convert
    /// @param a the augmentation factor. A value of 1 applies translation, 0 doesn't.
    /// @return the converted vector
    vector_type convert_to_parent(vector_type v, T a = 1) const {
        return vector_type(transform_matrix() * augmented_vector_type(v, a));
    }

    /// Converts the passed vector from the parent's coordinate space to this layer's coordinate space.
    ///
    /// @param v the vector to convert
    /// @param a the augmentation factor. A value of 1 applies translation, 0 doesn't.
    /// @return the converted vector
    vector_type convert_from_parent(vector_type v, T a = 1) const {
        return vector_type(inverse_transform_matrix() * augmented_vector_type(v, a));
    }

    /// Creates a matrix to convert points from this coordinate space to the other coordinate space.
    ///
    /// @param other The space to convert points to
    /// @return A matrix to convert points between the spaces
    /// @throws CoordinateSpaceException if the other space is unrelated to this one
    matrix_type conversion_matrix_to(CoordinateSpace<d, T, Q> *other) const {
        if(other == this) {
            return glm::identity<matrix_type>();
        }

        std::vector<space_type *> our_ancestors{};
        for(auto s = this; s != nullptr; s = s->parent_space()) {
            our_ancestors.push_back(s);
        }
        std::vector<space_type *> other_ancestors{};
        for(auto s = other; s != nullptr; s = s->parent_space()) {
            other_ancestors.push_back(s);
        }

        if(other_ancestors[other_ancestors.size() - 1] != our_ancestors[our_ancestors.size() - 1]) {
            throw CoordinateSpaceException("Unrelated coordinate spaces");
        }

        int our_lca_index = 0;
        int other_lca_index = 0;
        for(int i = 1; i <= min(our_ancestors.size(), other_ancestors.size()); ++i) {
            auto our_index = our_ancestors.size() - i;
            auto other_index = other_ancestors.size() - i;

            if(other_ancestors[other_index] == our_ancestors[our_index]) {
                our_lca_index = our_index;
                other_lca_index = other_index;
            } else {
                break;
            }
        }

        matrix_type conversion_matrix = glm::identity<matrix_type>();

        for(int i = 0; i < our_lca_index; ++i) {
            conversion_matrix = our_ancestors[i]->transform_matrix() * conversion_matrix;
        }

        for(int i = other_lca_index - 1; i >= 0; --i) {
            conversion_matrix = other_ancestors[i]->inverse_transform_matrix() * conversion_matrix;
        }

        return conversion_matrix;
    }

    /// Creates a matrix to convert points to this coordinate space from the other coordinate space.
    ///
    /// @param other The space to convert points from
    /// @return A matrix to convert points between the spaces
    /// @throws CoordinateSpaceException if the other space is unrelated to this one
    matrix_type conversion_matrix_from(CoordinateSpace<d, T, Q> *other) const {
        return other->conversion_matrix_to(this);
    }

protected:
    /// Gets a pointer to the parent coordinate space. The returned value must stay alive until the end of the current
    /// conversion method.
    ///
    /// @return The parent coordinate space or `nullptr` if this space has no parent
    virtual CoordinateSpace<d, T, Q> *parent_space() const = 0;
};

} // namespace facade

#endif // CHAOSEQUATIONS_COORDINATESPACE_H
