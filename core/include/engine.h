#ifndef ENGINE
#define ENGINE

#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you
#include <camera.h>
#include <drawable2d.h>
#include <ft2build.h>
#include <input.h>
#include <label.h>
#include <resource_manager.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include FT_FREETYPE_H


namespace GPE
{
    class Engine
    {
    public:
        enum class RunStatus : unsigned char
        {
            UNINITED,
            INITED,
            RUNNING,
            QUITTING
        };
        RunStatus status = RunStatus::UNINITED;

    private:
        int screen_width, screen_height;

        const char* window_name;
        const char* app_name;

        glm::vec4 bg_color;

        GLFWwindow* window;

        Camera camera{};

    public:
        Input input;

    private:
        float deltaTime = 0.0f;
        float timeNow = 0.0f;
        float lastFrame = 0.0f;

        // std::vector<std::unique_ptr<Drawable2D>> visible_on_screen;
        std::vector<std::shared_ptr<Drawable2D>> visible_on_screen;
        std::vector<std::shared_ptr<Drawable2D>> hidden_on_screen;

        void draw_and_update_objs();
        void free_objs();

    public:
        void init();
        void update();
        bool should_quit();
        void queue_quit();
        void quit();

        template <typename T>
        std::shared_ptr<T> create_object(std::unique_ptr<Drawable2D>&& obj)
        {
            return std::static_pointer_cast<T>(visible_on_screen.emplace_back(std::move(obj)));
        }

        void draw(std::shared_ptr<Drawable2D> obj);
        void delete_object(std::unique_ptr<Drawable2D>& obj) { obj.reset(); }

        void hide_on_screen(std::shared_ptr<Drawable2D> obj);
        void show_on_screen(std::shared_ptr<Drawable2D> obj);

        float get_deltaTime() const { return deltaTime; }
        float get_time() const { return timeNow; }

        void set_bg_color(const glm::vec4& new_color);
        glm::vec4 get_bg_color() const;

        static void print_str(const char* str);

        glm::vec3 get_screen_center() const
        {
            return glm::vec3(screen_width / 2.0f, screen_height / 2.0f, 0.0f);
        }
        GLFWwindow* get_window() const { return window; }

        explicit Engine(const char* name, int screen_width, int screen_height,
                        Input&& input = Input(),
                        const glm::vec4& bg_color = {0.1f, 0.1f, 0.1f, 1.0f});
        ~Engine() = default;
    };

    // template <typename T>
    // T* Engine::create_object(std::unique_ptr<Drawable2D>&& obj)
    // {
    //     T* raw = static_cast<T*>(obj.get());
    //     visible_on_screen.push_back(std::move(obj));
    //     return raw;
    // }

}  // namespace GPE

#endif
