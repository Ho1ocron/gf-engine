#ifndef FONT_H
#define FONT_H
#include <texture.h>

#include <array>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>

// TODO: ignore first unprintable characters
// TODO: add languages
constexpr size_t NUM_CHARACTERS = 128;

class FontAtlas {
    struct Character {
        // unsigned int TextureID;
        unsigned int Advance;
        glm::ivec2 size;
        glm::ivec2 offset;
        glm::vec2 top_left;
        glm::vec2 bottom_right;
    };

    std::array<Character, NUM_CHARACTERS> _characters;
    Texture _texture;
    unsigned int _height;
    Texture init_atlas(const char* path, const unsigned int& height);

public:
    const Character& get_char(const char value) const;

    const Texture& get_texture() const;
    const unsigned int& get_height() const;
    void use() const;
    FontAtlas(const char* path, const unsigned int& height);
};
#endif
