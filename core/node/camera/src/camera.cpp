#ifndef CAMERA_CPP
#define CAMERA_CPP

#include <camera.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace GPE
{
    glm::mat4x4 Camera::get_view_projection() const
    {
        glm::mat4x4 view{1.0f};
        view[3] = glm::vec4(pos, 0.0f, 1.0f);
        return glm::ortho(-_dimensions.x / 2.0f / zoom, _dimensions.x / 2.0f / zoom,
                          -_dimensions.y / 2.0f / zoom, _dimensions.y / 2.0f / zoom, 0.0f, 1.0f) *
               view;
    }

    glm::vec2 Camera::get_dimensions() const { return _dimensions; }
    void Camera::set_dimensions(const uint w, const uint h) { _dimensions = {w, h}; }

}  // namespace GPE
#endif