#ifndef INPUT_H
#define INPUT_H

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

        void set_callback(const std::function<void(State state)> & callback);
        void set_callback(const std::function<void(State state)> & callback,
                          const CallbackMode mode);
        void set_callback_mode(const CallbackMode mode);

        void set_static_user_data(void* other);

        Action(const CallbackMode callback_mode = CallbackMode::NEVER,
                         const std::function<void(State state)> & callback= nullptr)
            : callback(callback), callback_mode(callback_mode)
        {
        }
    };


    // TODO: make it a template and use T* instead of void*
    class Input
    {
    public:
        using ActionId = unsigned short;  // 2 bytes
        using Key = unsigned short;       // 2 bytes
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
