#include <gfe/engine/engine.h>


namespace GPE
{
    // template <typename T>
    // T* Engine::create_object(std::unique_ptr<Drawable2D>&& obj)
    // {
    //     // std::shared_ptr<Drawable2D> ptr{obj};
    //     // visible_on_screen.push_back(std::shared_ptr<Drawable2D>(obj));
    //     // visible_on_screen.push_back(std::unique_ptr<Drawable2D>(obj));
    //     // auto rptr = static_cast<type*>();
    //     T* obj_ptr = static_cast<T*>(obj.get());
    //     visible_on_screen.push_back(std::move(obj));
    //     return obj_ptr;
    // }

    void Engine::draw(std::shared_ptr<Drawable2D> obj) { obj->draw(); }

    void Engine::draw_and_update_objs()
    {
        for(auto& obj : visible_on_screen)
        {
            // we should separate drawing and updating since invisible object can be updated
            obj->draw();
            obj->update(deltaTime, screen_width, screen_height);
        }

        // for(auto& obj : hidden_on_screen) { obj->update(deltaTime, screen_width, screen_height);
        // }
    }

    void Engine::set_bg_color(const glm::vec4& new_color) { bg_color = new_color; }

    glm::vec4 Engine::get_bg_color() const { return bg_color; }

    void Engine::print_str(const char* str) { printf("%s\n", str); }

    Engine::Engine(const char* name, int screen_width, int screen_height, Input&& input,
                   const glm::vec4& bg_color)
        : app_name(name),
          screen_height(screen_height),
          screen_width(screen_width),
          input(std::move(input)),
          bg_color(bg_color)
    {
    }

    void Engine::free_objs()
    {
        if(!visible_on_screen.empty())
        {
            for(auto& obj : visible_on_screen) { obj.reset(); }
        }
        if(!hidden_on_screen.empty())
        {
            for(auto& obj : hidden_on_screen) { obj.reset(); }
        }

        visible_on_screen.clear();
        hidden_on_screen.clear();
    }

    bool Engine::should_quit()
    {
        // TODO: set status with glfwSetWindowCloseCallback()
        return status == RunStatus::QUITTING || (window && glfwWindowShouldClose(window));
    }
    void Engine::queue_quit() { status = RunStatus::QUITTING; }

    void Engine::quit()
    {
        free_objs();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Engine::init()
    {
        status = RunStatus::UNINITED;
        if(!glfwInit())
        {
            printf("Failed to initialize GLFW\n");
            return;  // make sure to exit or handle this case
        }
        // GLFWwindow* out;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHintString(GLFW_X11_CLASS_NAME, "graphics-engine");
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "graphics-engine");

#ifdef __APPLE__
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
        glfwInitHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
        window = glfwCreateWindow(screen_width, screen_height, app_name, nullptr, nullptr);
        if(!window)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
            glfwTerminate();
            return;
        }

        glfwGetFramebufferSize(window, &screen_width, &screen_height);
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window,
                           [](GLFWwindow* window, int key, int scancode, int action, int mods)
                           {
                               if(action == GLFW_REPEAT) return;
                               static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                   ->input.key_cb(static_cast<Input::Key>(key),
                                                  action == GLFW_PRESS, mods);
                           });
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


        camera.set_dimensions(screen_width, screen_height);

        glfwSetFramebufferSizeCallback(
            window,
            [](GLFWwindow* window, int w, int h)
            {
                glViewport(0, 0, w, h);
                Engine*&& app = static_cast<Engine*>(glfwGetWindowUserPointer(window));
                if(!app) return;
                app->camera.set_dimensions(w, h);
            });

        glViewport(0, 0, screen_width, screen_height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        status = RunStatus::INITED;
    }

    void Engine::update()
    {
        timeNow = glfwGetTime();
        deltaTime = timeNow - lastFrame;
        lastFrame = timeNow;

        glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        const glm::mat4x4&& VP = camera.get_view_projection();

        input.frame_update();
        draw_and_update_objs();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}  // namespace GPE
