#ifndef TEXTURE_CPP
#define TEXTURE_CPP
#include <glad/glad.h>
#include <texture.h>


Texture::Texture(const unsigned int id, const unsigned int w, const unsigned int h) : _id(id), _w(w), _h(h) {}

void Texture::use(const TextureUnits& texture_unit) const {
    glActiveTexture(GL_TEXTURE0 + static_cast<unsigned char>(texture_unit));
    glBindTexture(GL_TEXTURE_2D, _id);
}
unsigned int Texture::w() const { return _w; }
unsigned int Texture::h() const { return _h; }
#endif
