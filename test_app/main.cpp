#include <array>
#include <cmath>


#ifdef __linux__
#include <filesystem>
#endif
// #include "app.h"
#include <engine.h>
#include <text.h>

#include "GLFW/glfw3.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BG_COLOR {0.1f, 0.1f, 0.1f, 1.0f}
#define YELLOW {1.0f, 1.0f, 0.0f}
#define BLUE {0.0f, 1.0f, 1.0f}

#define CHARACTER "@*>"


GPE::Vec3 dynamic_gradient(float time)
{
    return GPE::Vec3{(sinf(time) + 1.0f) / 2.0f, (cosf(time) + 1.0f) / 2.0f, 0.5f};
}


std::vector<std::shared_ptr<GPE::Text>> texts;

enum class Actions : GPE::Input::ActionId
{
    QUIT,
    PRINT_HELLO,
    MAX
};

int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    std::array<GPE::Action, static_cast<size_t>(Actions::MAX)> actions;

    GPE::Engine engine{"My App", SCREEN_WIDTH, SCREEN_HEIGHT, {actions.data()}, BG_COLOR};
    engine.input.bind_key(GLFW_KEY_ENTER, Actions::PRINT_HELLO)
        .set_callback([&engine](GPE::Action::State) { engine.print_str("HELLO"); },
                      GPE::Action::CallbackMode::JUST_PRESS);
    // engine.input.bind_key(GLFW_KEY_ESCAPE, Actions::QUIT);
    engine.input.bind_key(GLFW_KEY_Q, Actions::QUIT);
    engine.input.bind_key(GLFW_KEY_ESCAPE, Actions::QUIT);
    engine.input.get_action(Actions::QUIT)
        .set_callback(
            [&engine](GPE::Action::State)
            {
                printf("Engine::queue_quit()\n");
                engine.queue_quit();
            },
            GPE::Action::CallbackMode::JUST_PRESS);
    engine.init();

    std::shared_ptr<GPE::Text> text1 =
        engine.create_object<GPE::Text>(std::move(std::make_unique<GPE::Text>(
            "Hello, World!", "assets/fonts/JetBrainsMono-Regular.ttf", GPE::Vec3{25.0f, 0.0f, 0.0f},
            52.0f, 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, GPE::Vec3 YELLOW)));

    text1->setPositionOnScreenCenter();

    for(int i = 0; i < 10; ++i)
    {
        texts.push_back(engine.create_object<GPE::Text>(std::move(std::make_unique<GPE::Text>(
            "Some text!", "assets/fonts/JetBrainsMono-Regular.ttf",
            GPE::Vec3{100.0f + 20.0f * (i % 2), SCREEN_HEIGHT - (float)30 * i, 0.0f}, 48.0f, 0.5f,
            SCREEN_WIDTH, SCREEN_HEIGHT, GPE::Vec3 YELLOW))));
    }

    while(!engine.should_quit())
    {
        for(std::shared_ptr<GPE::Text>& obj : texts)
        {
            obj->setColor(dynamic_gradient(engine.get_time() + 10.0f));
        }
        text1->setColor(dynamic_gradient(engine.get_time()));
        engine.update();
    }

    engine.quit();
    return 0;
}
