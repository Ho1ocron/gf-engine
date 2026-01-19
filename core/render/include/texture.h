#ifndef TEXTURE_H
#define TEXTURE_H
#include <core_constants.h>
#include <glad/glad.h>

class Texture
{
    GLuint _id;
    unsigned int _w, _h;

public:
    // only get resources from ResourceManager
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(const unsigned int id, const unsigned int w, const unsigned int h);
    void use(const TextureUnits& texture_unit) const;

    unsigned int w() const;
    unsigned int h() const;
};

#endif
