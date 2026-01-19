#ifndef GPE_INPUT_H
#define GPE_INPUT_H

#include <functional>


namespace GPE
{
    enum class Key
    {
        KEY_UNKNOWN = -1,
        KEY_A = 0,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_ESCAPE,
        KEY_LCTRL,
        KEY_LSHIFT,
        KEY_LALT,
        KEY_SPACE,
        // add other keys
    };

    enum class KeyStatus
    {
        Pressed,
        Released,
        Held
    };

    struct Input
    {
    public:
        void bind_key_action(const char* action_name, Key key, KeyStatus key_status);
        void unbind_key_action(const char* action_name);
        void key_action(const char* action_name, std::function<void()>);


        Input() = default;
        virtual ~Input() = default;
    };
}  // namespace GPE

#endif