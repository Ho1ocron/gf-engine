#pragma once

#include <ft2build.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include FT_FREETYPE_H

// #include <shader.h>
#include <gfe/core/render/shader.h>
#include <gfe/nodes/idrawable/idrawable.h>


namespace GPE
{

    struct Character
    {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };


    struct Font
    {
        std::map<char, Character> characters;
    };


    struct Text : Drawable2D
    {
    public:
        explicit Text(const char* text, const char* fontPath, glm::vec3 position, float fontSize,
                      float scale, const unsigned int& screen_width,
                      const unsigned int& screen_height, glm::vec3 color);

        void draw() override;
        void move(const glm::vec3& new_position) override;
        void update(const float& deltaTime, const unsigned int& screen_width,
                    const unsigned int& screen_height) override;
        void free() override;

        // void setScreenSize(const unsigned int& width, const unsigned int& height);

        void setText(const std::string& new_text) { content = new_text; }
        std::string getText() const { return content; }

        void setPosition(const glm::vec3& new_position) { position = new_position; }
        glm::vec3 getPosition() const { return position; }

        void setPositionOnScreenCenter();
        glm::vec2 getTextCenter() const;

        void setFontSize(float new_size) { fontSize = new_size; }
        float getFontSize() const { return fontSize; }

        glm::vec3 getSize() const
        {
            return glm::vec3(content.length() * fontSize * scale, fontSize * scale, 0.0f);
        }
        glm::vec3 getCenter() const { return position + getSize() * 0.5f; }

        void setScale(float new_scale) { scale = new_scale; }
        float getScale() const { return scale; }

        void setColor(const glm::vec3& new_color) { color = new_color; }
        glm::vec3 getColor() const { return color; }

    protected:
        void loadFont(const std::string& path, float& size);
        void setupBuffers();

        const unsigned int screen_width;
        const unsigned int screen_height;
        std::string content;
        glm::vec3 position;
        float fontSize;
        float scale;
        glm::vec3 color;

        Font font;
        Shader shader;

        glm::vec2 calculateTextDimensions() const;

        unsigned int VBO{};
        unsigned int VAO{};
    };
}  // namespace GPE
