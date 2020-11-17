#include <albedo/Uniform.h>

namespace albedo {

// glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxCombinedTextureImageUnits);

GLuint TextureUnitAllocator::reserve(GLenum target, GLuint texture) {
    auto entry = texture_units.emplace(BindInfo{target, texture}, next_unit);
    if (entry.second) { // no entry existed yet
        next_unit++;
    }
    return entry.first->second;
}

void TextureUnitAllocator::bind() {
    for (auto &[info, unit] : texture_units) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(info.target);
        glBindTexture(info.target, info.texture);
    }
}

void TextureUnitAllocator::unbind() {
    for (auto &[info, unit] : texture_units) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(info.target);
        glBindTexture(info.target, 0);
        glDisable(info.target);
    }
}

} // namespace albedo
