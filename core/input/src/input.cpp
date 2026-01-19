#include <input.h>

#include <algorithm>
#include <cstdio>

namespace GPE
{

    Action& Action::update(const bool press_or_release)
    {
        if(press_or_release)
        {
            m_count++;
            // well it should never become 0 after operator++() but...
            if(m_count != m_count.min)
                m_state = is_released() ? State::JUST_PRESSED : State::PRESSED;
        }
        else
        {
            m_count--;
            if(m_count == m_count.min)
                m_state = is_pressed() ? State::JUST_RELEASED : State::RELEASED;
        }

        if(callback)
        {
            switch(callback_mode)
            {
                case CallbackMode::PRESS:
                    if(is_pressed()) callback(m_state);
                    break;
                case CallbackMode::RELEASE:
                    if(is_released()) callback(m_state);
                    break;
                case CallbackMode::JUST_PRESS:
                    if(is_just_pressed()) callback(m_state);
                    break;
                case CallbackMode::JUST_RELEASE:
                    if(is_just_released()) callback(m_state);
                    break;
                case CallbackMode::JUST_BOTH:
                    if(is_just_pressed() || is_just_released()) callback(m_state);
                    break;

                case CallbackMode::BOTH:
                    callback(m_state);
                case CallbackMode::NEVER:
                    break;
            }
        }
        return *this;
    }


    void Input::unbind_key(const Input::Key key)
    {
        auto it = std::lower_bound(_binds.begin(), _binds.end(), key);
        if(it != _binds.end()) _binds.erase(it);
    }

    bool Action::is_pressed() const
    {
        return m_state == State::PRESSED || m_state == State::JUST_PRESSED;
    }
    bool Action::is_released() const
    {
        return m_state == State::RELEASED || m_state == State::JUST_RELEASED;
    }
    bool Action::is_just_pressed() const { return m_state == State::JUST_PRESSED; }
    bool Action::is_just_released() const { return m_state == State::JUST_RELEASED; }

    void Action::set_callback(const std::function<void(State state)>& callback)
    {
        this->callback = callback;
    }
    void Action::set_callback(const std::function<void(State state)>& callback,
                              const CallbackMode mode)
    {
        this->callback = callback;
        this->callback_mode = mode;
    }
    void Action::set_callback_mode(const CallbackMode mode) { this->callback_mode = mode; }

    void Input::key_cb(Input::Key key, const ButtonState state, const int mods)
    {
        auto it = std::lower_bound(_binds.begin(), _binds.end(), key);
        bool found = it != _binds.end() && it->key == key;
        if(!found) return;

        const Action& action = actions_array[it->action].update(state);
        if(action.is_just_pressed())
            _just_pressed_actions.push_back(it->action);
        else if(action.is_just_released())
            _just_released_actions.push_back(it->action);
    }
    Input::Input(ActionsArray actions) : actions_array(actions.ptr)
    {
        _just_pressed_actions.reserve(actions.count);
        _just_released_actions.reserve(actions.count);
    }
    Input::Input(ActionsArray actions, std::vector<_bindpair>&& binds)
        : actions_array(actions.ptr), _binds(std::move(binds))
    {
        _just_pressed_actions.reserve(actions.count);
        _just_released_actions.reserve(actions.count);
    }
    void Action::set_static_user_data(void* other) { static_user_data = other; }
    void Input::frame_update()
    {
        for(auto&& it = _just_pressed_actions.rbegin(); it != _just_pressed_actions.rend(); it++)
        {
            get_action(*it).m_state = Action::State::PRESSED;
            _just_pressed_actions.pop_back();
        }
        for(auto&& it = _just_released_actions.rbegin(); it != _just_released_actions.rend(); it++)
        {
            get_action(*it).m_state = Action::State::RELEASED;
            _just_released_actions.pop_back();
        }
    };
}  // namespace GPE
