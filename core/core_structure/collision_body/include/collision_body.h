#pragma once

#include <drawable2d.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

namespace GPE
{
    struct CollisionBody : Drawable2D
    {
    protected:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 velocity;
        float speed;
        glm::vec3 acceleration;
        glm::vec3 size;

    public:
        CollisionBody(const glm::vec3& position = glm::vec3(0.0f),
                      const glm::vec3& direction = glm::vec3(0.0f),
                      const glm::vec3& velocity = glm::vec3(0.0f), const float& speed = 0.0f,
                      const glm::vec3& acceleration = glm::vec3(0.0f),
                      const glm::vec3& size = glm::vec3(0.0f))
            : position(position),
              direction(direction),
              size(size),
              velocity(velocity),
              speed(speed),
              acceleration(acceleration)
        {
        }

        void setPosition(const glm::vec3& new_position);
        glm::vec3 getPosition() const;

        void setVelocity(const glm::vec3& new_velocity);
        glm::vec3 getVelocity() const;

        void setAcceleration(const glm::vec3& new_acceleration);
        glm::vec3 getAcceleration() const;

        void setSize(const glm::vec3& new_size);
        glm::vec3 getSize() const;

        virtual void draw() override = 0;

        virtual void update(const float& deltaTime, const unsigned int& screen_width,
                            const unsigned int& screen_height) override = 0;

        virtual void free() override = 0;
    };
}  // namespace GPE