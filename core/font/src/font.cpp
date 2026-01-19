#ifndef FONT_CPP
#define FONT_CPP
#include <constants.h>
#include <font.h>
#include <freetype/freetype.h>
#include <texture.h>

// not in constructor because of Texture(const Texture&) = delete;
Texture FontAtlas::init_atlas(const char* path, const unsigned int& height) {
    FT_Library ft;
    if(const auto err = FT_Init_FreeType(&ft)) {
        printf("TODO: log library INIT (%d)\n", err);
        // TODO: LOGERRRET macro
        return Texture(0, 0, 0);
    }
    FT_Face face;
    if(const auto err = FT_New_Face(ft, path, 0, &face)) {
        printf("TODO: log library FACE (%d) %s\n", err, path);
        return Texture(0, 0, 0);
    }
    FT_Set_Pixel_Sizes(face, 0, height);
    unsigned int w = 0, h = 0;
    for(unsigned char c = 0; c < NUM_CHARACTERS; c++ /* :0 */) {
        if(FT_Load_Char(face, static_cast<char>(c), FT_LOAD_RENDER)) {
            printf("ERROR::FREETYPE: FT_Load_Char(i = %u) != 0\n", c);
            continue;
        }
        w += face->glyph->bitmap.width;
        h = std::max(h, face->glyph->bitmap.rows);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (int)w, (int)h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);


    printf("ATLAS W: %u H: %u\n", w, h);
    unsigned long x = 0;
    for(unsigned char c = 0; c < NUM_CHARACTERS; c++ /* d:D */) {
        if(FT_Load_Char(face, static_cast<char>(c), FT_LOAD_RENDER)) {
            printf("ERROR::FREETYPE: FT_Load_Char(i = %u) != 0\n", c);
            continue;
        }
        const unsigned int& cw = face->glyph->bitmap.width;
        const unsigned int& ch = face->glyph->bitmap.rows;
        glTexSubImage2D(GL_TEXTURE_2D, 0, (int)x, 0, (int)cw, (int)ch, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        Character character;
        character.size = {cw, ch};
        character.offset = {face->glyph->bitmap_left, ch - face->glyph->bitmap_top};
        character.Advance = face->glyph->advance.x;
        character.top_left = {float(x) / float(w), 0.0f};
        character.bottom_right = {float(x + cw) / float(w), float(ch) / float(h)};
        _characters[c] = character;

        x += cw;
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glBindTexture(GL_TEXTURE_2D, 0);

    return Texture(texture, w, h);
}

const Texture& FontAtlas::get_texture() const { return _texture; }
const unsigned int& FontAtlas::get_height() const { return _height; }
const FontAtlas::Character& FontAtlas::get_char(const char value) const {
    if(value > _characters.size())
        return _characters['?'];
    else
        return _characters[value];
}
void FontAtlas::use() const { _texture.use(TextureUnits::FONT_ATLAS); }

FontAtlas::FontAtlas(const char* path, const unsigned int& height) : _height(height), _texture(init_atlas(path, height)) {}


#endif
