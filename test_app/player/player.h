#pragma once

#include <GLFW/glfw3.h>
#include <character_body_2d.h>

#include "text.h"

#define FONT_DIR "assets/font"
#define BOLD_FONT "JetBrainsMono-Bold.ttf"


class Player : public GPE::CharacterBody2D
{
private:
    glm::vec3 size;
    unsigned int screen_width;
    unsigned int screen_height;
    GLFWwindow* window = nullptr;
    static constexpr const char* default_font_path = FONT_DIR BOLD_FONT;

public:
    Player(unsigned int screen_width, unsigned int screen_height, GLFWwindow* app_window,
           const glm::vec3& init_position = glm::vec3{0.0f}, const float& _speed = 1000.0f,
           const char* text = "@", const char* font_path = default_font_path,
           float font_size = 48.0f, float scale = 1.0f, const glm::vec3& color = glm::vec3{1.0f})
        : CharacterBody2D(std::make_unique<GPE::Text>(text, font_path, init_position, font_size,
                                                      scale, screen_width, screen_height, color))
    {
        position = init_position;
        speed = _speed;
        window = app_window;
        this->screen_width = screen_width;
        this->screen_height = screen_height;
    }

    void setScreenSize(const unsigned int& new_screen_width, const unsigned int& new_screen_height)
    {
        screen_width = new_screen_width;
        screen_height = new_screen_height;
    }

    void input()
    {
        direction = glm::vec3(0.0f);  // RESET EVERY FRAME

        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { direction.y += 1.0f; }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { direction.y -= 1.0f; }
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { direction.x -= 1.0f; }
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { direction.x += 1.0f; }

        if(glm::length(direction) > 0.0f) direction = glm::normalize(direction);
    }
    void update(const float& deltaTime, const unsigned int& screen_width,
                const unsigned int& screen_height) override;
};


void Player::update(const float& deltaTime, const unsigned int& screen_width,
                    const unsigned int& screen_height)
{
    input();
    move(deltaTime, 1600.0f, 1200.0f);
    updateSprite(screen_width, screen_height);
}