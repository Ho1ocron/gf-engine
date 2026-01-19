#pragma once

#include <glm/glm.hpp>


namespace GPE
{
    struct Drawable2D
    {
        virtual ~Drawable2D() = default;

        virtual void update(const float& deltaTime, const unsigned int& screen_width,
                            const unsigned int& screen_height) = 0;

        virtual void move(const glm::vec3& new_position) { return; }

        virtual void draw() = 0;

        virtual void free() = 0;
    };
}  // namespace GPE