#pragma once

#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you

#include <camera.h>
#include <ft2build.h>
#include <label.h>
#include <resource_manager.h>

#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include FT_FREETYPE_H


template <class T>
struct DrawableContainer
{
    using StaticResources = typename T::StaticResources;

    std::vector<std::unique_ptr<T>> objects;
    StaticResources draw_resources;

    void draw(const glm::mat4x4& VP)
    {
        draw_resources.use();
        for(const auto& obj : objects) { obj->draw(draw_resources, VP); }
    }

    // if StaticResources(ResourceManager&) exists, you may use
    // DrawableContainer(resource_manager)
    DrawableContainer(StaticResources res) : draw_resources(res) {}
};

class MyApp
{
private:
    const char* title;
    int SCR_WIDTH, SCR_HEIGHT;

    GLFWwindow* window = nullptr;

    ResourceManager resource_manager{"core/assets/shaders/", "assets/fonts/"};

    // std::vector<std::unique_ptr<Label>> labels;
    // Label::StaticResources label_static_resources;
public:
    DrawableContainer<Label> labels;

private:
    Camera camera{};
    float deltaTime = 0.0f;
    float timeNow = 0.0f;
    float lastFrame = 0.0f;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void draw_labels();

public:
    GLFWwindow* get_window() { return window; }
    float get_delta() const { return deltaTime; }
    float get_time() const { return timeNow; }
    Label& push_label(std::unique_ptr<Label>&& obj);
    Label& emplace_label(const char* text, const char* font_name, const Label::Alignment alignment = Label::Alignment::LEFT, const glm::vec2& pos = {0.0, 0.0},
                         const float& height = 36, const glm::vec3& color = {1.0, 1.0, 1.0});
    // user should load OpenGL on their own
    static GLFWwindow* create_window(const char* title, const unsigned int w, const unsigned int h);

    void run(const std::function<void()>& on_update = nullptr);

    MyApp(GLFWwindow*&& window, const char* app_title = nullptr);
};
