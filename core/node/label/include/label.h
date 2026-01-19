#ifndef LABEL_HPP
#define LABEL_HPP

#include <font.h>
#include <resource_manager.h>
#include <shader.h>

#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <string_view>


namespace GPE
{
    class Label
    {
    public:
        std::shared_ptr<FontAtlas> _font;
        GLuint _VBO, _EBO, _VAO;
        unsigned int _len;

        glm::vec2 pos{};
        glm::vec3 color{1.0, 1.0, 1.0};

        struct CharVertex
        {
            glm::vec2 pos;
            glm::vec2 tex_pos;
        };
        struct SingleCharacter
        {
            CharVertex top_left;      // 0
            CharVertex top_right;     // 1
            CharVertex bottom_left;   // 2
            CharVertex bottom_right;  // 3
        };
        constexpr static size_t VERTICES_COUNT = 4;
        constexpr static size_t INDICES_COUNT = 6;  // 6 indices for 4 vertices
        // KEEP_OLD is used in set_text() to not use std::optional
        enum class Alignment : char
        {
            LEFT,
            MIDDLE,
            RIGHT,
            KEEP_OLD
        };


    private:
        Alignment _alignment;
        glm::mat4x4 get_model() const;

    public:
        struct StaticResources
        {
            const std::shared_ptr<Shader> shader;

        public:
            void use() const { shader->use(); }

            StaticResources(const std::shared_ptr<Shader>& shader) : shader(shader)
            {
                shader->use();
                shader->setInt("font", static_cast<int>(TextureUnits::FONT_ATLAS));
            }
            StaticResources(ResourceManager& resource_manager)
                : StaticResources(resource_manager.get_shader<ShaderID::TEXT>())
            {
            }
        };

    public:
        // refills VBO and EBO, so please do not use frequently
        Label& set_text(const char* buf, const size_t& len,
                        const Alignment alignment = Alignment::KEEP_OLD);
        Label& set_text(const std::string_view& str,
                        const Alignment alignment = Alignment::KEEP_OLD);
        Label& set_color(const glm::vec3& color);
        Label& set_pos(const glm::vec2& pos);

        void draw(const StaticResources& res, const glm::mat4x4 VP) const;
        Label(const std::shared_ptr<FontAtlas>& font, const glm::vec2& pos = {0.0, 0.0},
              const glm::vec3& color = {1.0, 1.0, 1.0}, const Alignment alignment = Alignment::LEFT,
              const char* buf = nullptr, const size_t len = 0);
    };
}  // namespace GPE

#endif