#pragma once

#include <collision_body.h>
#include <drawable2d.h>
#include <glad/glad.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <memory>
#include <type_traits>
#include <variant>

#include "collision_shape_2d.h"

namespace GPE
{
    // template<class Drawable2D>
    struct CharacterBody2D : CollisionBody
    {
    protected:
        std::unique_ptr<Drawable2D> sprite;
        std::unique_ptr<CircleCollisionShape2D> hitbox;

    public:
        explicit CharacterBody2D(std::unique_ptr<Drawable2D> new_sprite)
            : sprite(std::move(new_sprite))
        {
        }

        void move(float deltaTime, float screen_width, float screen_hight);

        void update(const float& deltaTime, const unsigned int& screen_width,
                    const unsigned int& screen_height) override;

        void updateSprite(unsigned int width, unsigned int height);

    private:
        void draw() override {}
        void free() override {}
    };
}  // namespace GPE