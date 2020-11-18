#ifndef CHAOSEQUATIONS_COLORS_H
#define CHAOSEQUATIONS_COLORS_H

#include <glm/vec4.hpp>

namespace ll {
constexpr glm::vec4 rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return {r / 255.0, g / 255.0, b / 255.0, a / 255.0};
}

constexpr glm::vec4 rgb(unsigned char r, unsigned char g, unsigned char b) { return rgba(r, g, b, 255); }

constexpr glm::vec4 rgb(unsigned int hex) { return rgb(hex >> 16 & 0xff, hex >> 8 & 0xff, hex >> 0 & 0xff); }

constexpr glm::vec4 rgba(unsigned int hex) {
    return rgba(hex >> 25 & 0xff, hex >> 16 & 0xff, hex >> 8 & 0xff, hex >> 0 & 0xff);
}

// https://sashamaps.net/docs/resources/20-colors/
namespace colors {
[[maybe_unused]] constexpr glm::vec4 red = rgb(0xe6194b);
[[maybe_unused]] constexpr glm::vec4 green = rgb(0x3cb44b);
[[maybe_unused]] constexpr glm::vec4 yellow = rgb(0xffe119);
[[maybe_unused]] constexpr glm::vec4 blue = rgb(0x4363d8);
[[maybe_unused]] constexpr glm::vec4 orange = rgb(0xf58231);
[[maybe_unused]] constexpr glm::vec4 purple = rgb(0x911eb4);
[[maybe_unused]] constexpr glm::vec4 cyan = rgb(0x42d4f4);
[[maybe_unused]] constexpr glm::vec4 magenta = rgb(0xf032e6);
[[maybe_unused]] constexpr glm::vec4 lime = rgb(0xbfef45);
[[maybe_unused]] constexpr glm::vec4 pink = rgb(0xfabed4);
[[maybe_unused]] constexpr glm::vec4 teal = rgb(0x469990);
[[maybe_unused]] constexpr glm::vec4 lavender = rgb(0xdcbeff);
[[maybe_unused]] constexpr glm::vec4 brown = rgb(0x9a6324);
[[maybe_unused]] constexpr glm::vec4 beige = rgb(0xfffac8);
[[maybe_unused]] constexpr glm::vec4 maroon = rgb(0x800000);
[[maybe_unused]] constexpr glm::vec4 mint = rgb(0xaaffc3);
[[maybe_unused]] constexpr glm::vec4 olive = rgb(0x808000);
[[maybe_unused]] constexpr glm::vec4 apricot = rgb(0xffd8b1);
[[maybe_unused]] constexpr glm::vec4 navy = rgb(0x000075);
[[maybe_unused]] constexpr glm::vec4 grey = rgb(0xa9a9a9);
[[maybe_unused]] constexpr glm::vec4 white = rgb(0xffffff);
[[maybe_unused]] constexpr glm::vec4 black = rgb(0x000000);

[[maybe_unused]] constexpr glm::vec4 pure_white = white;
[[maybe_unused]] constexpr glm::vec4 pure_black = black;
[[maybe_unused]] constexpr glm::vec4 pure_red = rgb(0xff0000);
[[maybe_unused]] constexpr glm::vec4 pure_green = rgb(0x00ff00);
[[maybe_unused]] constexpr glm::vec4 pure_blue = rgb(0x0000ff);
[[maybe_unused]] constexpr glm::vec4 pure_cyan = rgb(0x00ffff);
[[maybe_unused]] constexpr glm::vec4 pure_magenta = rgb(0xff00ff);
[[maybe_unused]] constexpr glm::vec4 pure_yellow = rgb(0xffff00);
}
} // namespace ll

#endif // CHAOSEQUATIONS_COLORS_H
