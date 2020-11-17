#ifndef CHAOSEQUATIONS_MATH_H
#define CHAOSEQUATIONS_MATH_H

#include <glm/vec2.hpp>
#include <vector>

namespace facade {

struct Transform {
    glm::vec2 pos;
};

template <typename T> struct Stack {
private:
    T value;
    std::vector<T> stack;

public:
    explicit Stack() : value() {}
    explicit Stack(const T &value) : value(value) {}
    Stack(const Stack &) = delete;

    inline void push() { stack.emplace_back(value); }

    inline void pop() {
        if (stack.empty())
            value = {};
        value = stack.pop_back();
    };

    inline int depth() { return stack.size(); }

    inline T &operator*() { return value; }

    inline T *operator->() { return &value; };
};

} // namespace facade

#endif // CHAOSEQUATIONS_MATH_H
