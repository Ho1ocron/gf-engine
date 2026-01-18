#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <bounded_counter.h>

#include <algorithm>
#include <functional>
#include <vector>


namespace GPE
{
    struct Action
    {
        enum class State : unsigned char
        {
            RELEASED,
            JUST_PRESSED,
            PRESSED,
            JUST_RELEASED,
        };
        enum class CallbackMode : unsigned char
        {
            NEVER,
            BOTH,  // call callback even if counter is 0 or max

            PRESS,    // call callback even if counter == counter.max
            RELEASE,  // call callback even if counter != 0

            JUST_PRESS,
            JUST_RELEASE,
            JUST_BOTH,
        };

        // void (*callback)(void* user_data, void* static_user_data, State state);
        std::function<void(State state)> callback;
        void* static_user_data = nullptr;
        BoundedCounter<unsigned char> m_count = 0;  // max 256 presses
        State m_state = State::RELEASED;
        CallbackMode callback_mode{};

        bool is_pressed() const;
        bool is_released() const;
        bool is_just_pressed() const;
        bool is_just_released() const;
        void update(const bool press_or_release, void* callback_data = nullptr);

        void set_callback(const std::function<void(State state)>& callback);
        void set_callback(const std::function<void(State state)>& callback,
                          const CallbackMode mode);
        void set_callback_mode(const CallbackMode mode);

        void set_static_user_data(void* other);

        Action(const CallbackMode callback_mode = CallbackMode::NEVER,
               const std::function<void(State state)>& callback = nullptr)
            : callback(callback), callback_mode(callback_mode)
        {
        }
    };


    // TODO: make it a template and use T* instead of void*
    class Input
    {
    public:
        enum Key : unsigned short  // 2 bytes
        {
            // Stolen from GLFW
            /* Printable keys */
            KEY_SPACE = GLFW_KEY_SPACE,
            KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE, /* ' */
            KEY_COMMA = GLFW_KEY_COMMA,           /* , */
            KEY_MINUS = GLFW_KEY_MINUS,           /* - */
            KEY_PERIOD = GLFW_KEY_PERIOD,         /* . */
            KEY_SLASH = GLFW_KEY_SLASH,           /* / */
            KEY_0 = GLFW_KEY_0,
            KEY_1 = GLFW_KEY_1,
            KEY_2 = GLFW_KEY_2,
            KEY_3 = GLFW_KEY_3,
            KEY_4 = GLFW_KEY_4,
            KEY_5 = GLFW_KEY_5,
            KEY_6 = GLFW_KEY_6,
            KEY_7 = GLFW_KEY_7,
            KEY_8 = GLFW_KEY_8,
            KEY_9 = GLFW_KEY_9,
            KEY_SEMICOLON = GLFW_KEY_SEMICOLON, /* ; */
            KEY_EQUAL = GLFW_KEY_EQUAL,         /* = */
            KEY_A = GLFW_KEY_A,
            KEY_B = GLFW_KEY_B,
            KEY_C = GLFW_KEY_C,
            KEY_D = GLFW_KEY_D,
            KEY_E = GLFW_KEY_E,
            KEY_F = GLFW_KEY_F,
            KEY_G = GLFW_KEY_G,
            KEY_H = GLFW_KEY_H,
            KEY_I = GLFW_KEY_I,
            KEY_J = GLFW_KEY_J,
            KEY_K = GLFW_KEY_K,
            KEY_L = GLFW_KEY_L,
            KEY_M = GLFW_KEY_M,
            KEY_N = GLFW_KEY_N,
            KEY_O = GLFW_KEY_O,
            KEY_P = GLFW_KEY_P,
            KEY_Q = GLFW_KEY_Q,
            KEY_R = GLFW_KEY_R,
            KEY_S = GLFW_KEY_S,
            KEY_T = GLFW_KEY_T,
            KEY_U = GLFW_KEY_U,
            KEY_V = GLFW_KEY_V,
            KEY_W = GLFW_KEY_W,
            KEY_X = GLFW_KEY_X,
            KEY_Y = GLFW_KEY_Y,
            KEY_Z = GLFW_KEY_Z,
            KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,   /* [ */
            KEY_BACKSLASH = GLFW_KEY_BACKSLASH,         /* \ */
            KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET, /* ] */
            KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,   /* ` */
            KEY_WORLD_1 = GLFW_KEY_WORLD_1,             /* non-US */
            KEY_WORLD_2 = GLFW_KEY_WORLD_2,             /* non-US nction keys */
            KEY_ESCAPE = GLFW_KEY_ESCAPE,
            KEY_ENTER = GLFW_KEY_ENTER,
            KEY_TAB = GLFW_KEY_TAB,
            KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
            KEY_INSERT = GLFW_KEY_INSERT,
            KEY_DELETE = GLFW_KEY_DELETE,
            KEY_RIGHT = GLFW_KEY_RIGHT,
            KEY_LEFT = GLFW_KEY_LEFT,
            KEY_DOWN = GLFW_KEY_DOWN,
            KEY_UP = GLFW_KEY_UP,
            KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
            KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
            KEY_HOME = GLFW_KEY_HOME,
            KEY_END = GLFW_KEY_END,
            KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
            KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
            KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
            KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
            KEY_PAUSE = GLFW_KEY_PAUSE,
            KEY_F1 = GLFW_KEY_F1,
            KEY_F2 = GLFW_KEY_F2,
            KEY_F3 = GLFW_KEY_F3,
            KEY_F4 = GLFW_KEY_F4,
            KEY_F5 = GLFW_KEY_F5,
            KEY_F6 = GLFW_KEY_F6,
            KEY_F7 = GLFW_KEY_F7,
            KEY_F8 = GLFW_KEY_F8,
            KEY_F9 = GLFW_KEY_F9,
            KEY_F10 = GLFW_KEY_F10,
            KEY_F11 = GLFW_KEY_F11,
            KEY_F12 = GLFW_KEY_F12,
            KEY_F13 = GLFW_KEY_F13,
            KEY_F14 = GLFW_KEY_F14,
            KEY_F15 = GLFW_KEY_F15,
            KEY_F16 = GLFW_KEY_F16,
            KEY_F17 = GLFW_KEY_F17,
            KEY_F18 = GLFW_KEY_F18,
            KEY_F19 = GLFW_KEY_F19,
            KEY_F20 = GLFW_KEY_F20,
            KEY_F21 = GLFW_KEY_F21,
            KEY_F22 = GLFW_KEY_F22,
            KEY_F23 = GLFW_KEY_F23,
            KEY_F24 = GLFW_KEY_F24,
            KEY_F25 = GLFW_KEY_F25,
            KEY_KP_0 = GLFW_KEY_KP_0,
            KEY_KP_1 = GLFW_KEY_KP_1,
            KEY_KP_2 = GLFW_KEY_KP_2,
            KEY_KP_3 = GLFW_KEY_KP_3,
            KEY_KP_4 = GLFW_KEY_KP_4,
            KEY_KP_5 = GLFW_KEY_KP_5,
            KEY_KP_6 = GLFW_KEY_KP_6,
            KEY_KP_7 = GLFW_KEY_KP_7,
            KEY_KP_8 = GLFW_KEY_KP_8,
            KEY_KP_9 = GLFW_KEY_KP_9,
            KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
            KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
            KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
            KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
            KEY_KP_ADD = GLFW_KEY_KP_ADD,
            KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
            KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
            KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
            KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
            KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
            KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
            KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
            KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
            KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
            KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
            KEY_MENU = GLFW_KEY_MENU,
            KEY_MAX,
        };
        using ActionId = unsigned short;  // 2 bytes
        struct ButtonState
        {
            enum State : bool
            {
                PRESS = true,
                RELEASE = false
            };
            State value;

            operator bool() const { return static_cast<bool>(value); }
            constexpr ButtonState(const bool value) : value(static_cast<State>(value)) {}
        };

    public:
        // std::vector<Action> actions;
        // const std::vector<Action> actions;
        Action* const actions_array;
        // const size_t actions_count;

    private:
        // using _bindpair = std::pair<Key, ActionId>;
        struct _bindpair
        {
            Key key;
            ActionId action;
            bool operator<(const Key key) const { return this->key < key; }
            bool operator<(const _bindpair other) const { return this->key < other.key; }
        };
        std::vector<_bindpair> _binds;

    public:
        void key_cb(Key key, const ButtonState state, const int mods, void* user_data);

        // @warning you should not pass action_id that is greater than the last action
        // because there is no overflow checks. Use enum with MAX member as last
        template <class T>
        inline Action& get_action(const T action_id) const
        {
            return actions_array[static_cast<size_t>(action_id)];
        }
        // @warning you should not pass action_id that is greater than the last action
        // because there is no overflow checks. Use enum with MAX member as last
        template <class T>
        Action& bind_key(const Input::Key key, const T action_id)
        {
            auto it = std::lower_bound(_binds.begin(), _binds.end(), key);
            bool found = it != _binds.end() && it->key == key;
            if(found)
            {
                if(it->key == key)
                    it->action = static_cast<ActionId>(action_id);
                else
                {
                    *it = {key, static_cast<ActionId>(action_id)};
                    // TODO: optimize it
                    std::sort(_binds.begin(), _binds.end());
                }
            }
            else
                _binds.insert(it, {key, static_cast<ActionId>(action_id)});
            return get_action(action_id);
        }
        void unbind_key(const Key key);

        Input(Action* const actions_array, std::vector<_bindpair>&& binds);
        Input(Action* const actions_array = nullptr);
    };

}  // namespace GPE
#endif
