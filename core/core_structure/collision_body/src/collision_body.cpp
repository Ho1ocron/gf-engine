#include "collision_body.h"

namespace GPE
{
    void CollisionBody::setPosition(const glm::vec3& new_position) { position = new_position; }
    glm::vec3 CollisionBody::getPosition() const { return position; }


    void CollisionBody::setVelocity(const glm::vec3& new_velocity) { velocity = new_velocity; }
    glm::vec3 CollisionBody::getVelocity() const { return velocity; }


    void CollisionBody::setAcceleration(const glm::vec3& new_acceleration)
    {
        acceleration = new_acceleration;
    }
    glm::vec3 CollisionBody::getAcceleration() const { return acceleration; }


    void CollisionBody::setSize(const glm::vec3& new_size) { size = new_size; }
    glm::vec3 CollisionBody::getSize() const { return size; }
}  // namespace GPE