#include "text.h"

#define SHADER_DIR "core/assets/old_shaders/"

namespace GFE
{
    Text::Text(const char* text, const char* fontPath, glm::vec3 position, float fontSize,
               float scale, const unsigned int& screen_width, const unsigned int& screen_height,
               glm::vec3 color)
        : content(text),
          position(position),
          fontSize(fontSize),
          scale(scale),
          screen_height(screen_height),
          screen_width(screen_width),
          color(color),
          shader(SHADER_DIR "text.vs", SHADER_DIR "text.fs")
    {
        loadFont(fontPath, fontSize);
        setupBuffers();

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screen_width), 0.0f,
                                          static_cast<float>(screen_height));
        shader.use();
        shader.setMat4("projection", projection);
    }


    void Text::loadFont(const std::string& path, float& size)
    {
        FT_Library ft;
        FT_Init_FreeType(&ft);

        FT_Face face;
        FT_New_Face(ft, path.c_str(), 0, &face);
        FT_Set_Pixel_Sizes(face, 0, size);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 0; c < 128; c++)
        {
            FT_Load_Char(face, c, FT_LOAD_RENDER);

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                         face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            font.characters[static_cast<char>(c)] = {
                texture,
                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                static_cast<unsigned int>(face->glyph->advance.x)};
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }


    void Text::setupBuffers()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // void Text::setScreenSize(const unsigned int& width, const unsigned int& height) {
    //     glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f,
    //     static_cast<float>(height)); shader.use(); shader.setMat4("projection", projection);
    // }

    glm::vec2 Text::calculateTextDimensions() const
    {
        float width = 0.0f;
        float height = 0.0f;

        for(const char& c : content)
        {
            auto it = font.characters.find(c);
            if(it == font.characters.end()) continue;

            const Character& ch = it->second;
            width += (ch.Advance >> 6) * scale;
            float charHeight = ch.Size.y * scale;
            if(charHeight > height) height = charHeight;
        }

        return glm::vec2(width, height);
    }

    void Text::setPositionOnScreenCenter()
    {
        glm::vec2 text_dimensions = calculateTextDimensions();
        position.x = (screen_width / 2.0f) - (text_dimensions.x / 2.0f);
        position.y = (screen_height / 2.0f) - (text_dimensions.y / 2.0f);
    }

    glm::vec2 Text::getTextCenter() const
    {
        glm::vec2 text_dimensions = calculateTextDimensions();
        return glm::vec2(position.x + text_dimensions.x / 2.0f,
                         position.y + text_dimensions.y / 2.0f);
    }


    void Text::draw()
    {
        shader.use();
        shader.setVec3("textColor", color);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        float x = position.x;
        float y = position.y;

        for(char c : content)
        {
            const Character& ch = font.characters.at(c);

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f},    {xpos, ypos, 0.0f, 1.0f},
                                    {xpos + w, ypos, 1.0f, 1.0f},

                                    {xpos, ypos + h, 0.0f, 0.0f},    {xpos + w, ypos, 1.0f, 1.0f},
                                    {xpos + w, ypos + h, 1.0f, 0.0f}};

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.Advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Text::update(const float& deltaTime, const unsigned int& screen_width,
                      const unsigned int& screen_height)
    {
        // position = new_position;
        // setScreenSize(screen_width, screen_height);
        // render();
        // draw();
    }


    void Text::move(const glm::vec3& new_position) { position = new_position; }
    // void Text::free()
    // {
    //     glDeleteVertexArrays(1, &VAO);
    //     glDeleteBuffers(1, &VBO);
    //     for(auto& pair : font.characters)
    //     {
    //         glDeleteTextures(1, &pair.second.TextureID);
    //     }
    // }
    void Text::free() { return; }
}  // namespace GFE