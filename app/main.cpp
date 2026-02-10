#ifdef __linux__
#include <filesystem>
#endif
#include <gfe/engine/engine.h>
// #include "app.h"
#include <gfe/core/constants/types.h>
#include <gfe/core/input/input.h>
#include <gfe/nodes/text/text.h>
// #include <gfe/nodes/label/label.h>

#include <array>
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BG_COLOR {0.1f, 0.1f, 0.1f, 1.0f}
#define YELLOW {1.0f, 1.0f, 0.0f}
#define BLUE {0.0f, 1.0f, 1.0f}

#define CHARACTER "@"


GPE::Vec3 dynamic_gradient(float time)
{
    return GPE::Vec3{(sinf(time) + 1.0f) / 2.0f, (cosf(time) + 1.0f) / 2.0f, 0.5f};
}


std::vector<std::shared_ptr<GPE::Text>> texts;

enum class Actions : uint16_t
{
    QUIT,
    PRINT_HELLO,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    ACTIONS_MAX,
};


class MvText : public GPE::Text
{
private:
    GPE::Engine& _engine;

public:
    void update(const float& deltaTime, const unsigned int& screen_width,
                const unsigned int& screen_height) override
    {
        const float moveSpeed = 500.0f;  // pixels per second
        // printf("Is key W pressed: %d\n",
        // _engine.input.get_action(Actions::MOVE_UP).is_pressed()); printf("Is key S pressed:
        // %d\n", _engine.input.get_action(Actions::K).is_pressed());

        if(_engine.input.get_action(Actions::MOVE_UP).is_pressed())
        {
            // printf("W is pressed\n");
            position.y += moveSpeed * deltaTime;
        }
        if(_engine.input.get_action(Actions::MOVE_DOWN).is_pressed())
        {
            position.y -= moveSpeed * deltaTime;
        }
        if(_engine.input.get_action(Actions::MOVE_RIGHT).is_pressed())
        {
            position.x += moveSpeed * deltaTime;
        }
        if(_engine.input.get_action(Actions::MOVE_LEFT).is_pressed())
        {
            position.x -= moveSpeed * deltaTime;
        }
    }

    MvText(GPE::Engine& engine, GPE::Vec3 init_pos)
        : GPE::Text(CHARACTER,                                 // initial text
                    "assets/fonts/JetBrainsMono-Regular.ttf",  // font path — must be valid!
                    init_pos,                                  // initial position
                    52.0f,                                     // font size
                    0.5f,                                      // scale
                    800,                                       // screen width (example)
                    600,                                       // screen height (example)
                    glm::vec3 BLUE                             // color (white)
                    ),
          _engine(engine)

    {
        _engine.input.bind_key(GPE::Input::Key::KEY_W, Actions::MOVE_UP);
        _engine.input.bind_key(GPE::Input::Key::KEY_S, Actions::MOVE_DOWN);
        _engine.input.bind_key(GPE::Input::Key::KEY_D, Actions::MOVE_RIGHT);
        _engine.input.bind_key(GPE::Input::Key::KEY_A, Actions::MOVE_LEFT);
    }
};


using GPE::Input;
int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    std::array<GPE::Action, static_cast<size_t>(Actions::ACTIONS_MAX)> actions;

    GPE::Engine engine{"My App", SCREEN_WIDTH, SCREEN_HEIGHT, {actions}, BG_COLOR};
    engine.input.bind_key(Input::KEY_ENTER, Actions::PRINT_HELLO)
        .set_callback([&engine](GPE::Action::State) { engine.print_str("HELLO"); },
                      GPE::Action::CallbackMode::JUST_PRESS);
    engine.input.bind_key(Input::KEY_Q, Actions::QUIT);
    engine.input.bind_key(Input::KEY_ESCAPE, Actions::QUIT);
    engine.input.get_action(Actions::QUIT)
        .set_callback(
            [&engine](GPE::Action::State)
            {
                printf("Engine::queue_quit()\n");
                engine.queue_quit();
            },
            GPE::Action::CallbackMode::JUST_PRESS);
    engine.init();

    std::shared_ptr<MvText> mv_text = engine.create_object<MvText>(
        std::move(std::make_unique<MvText>(engine, GPE::Vec3{100.0f, 100.0f, 0.0f})));
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
        if(engine.input.get_action(Actions::PRINT_HELLO).is_just_pressed())
        {
            printf("PRINT_HELLO JUST PRESSED\n");
        }
    }

    engine.quit();
    return 0;
}
