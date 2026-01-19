#include "app.h"

#include <font.h>
#include <label.h>
#include <resource_manager.h>

#include <iterator>
#include <memory>
// #include "player/player.h"


Label& MyApp::emplace_label(const char* text, const char* font_name, const Label::Alignment alignment, const glm::vec2& pos, const float& height,
                            const glm::vec3& color) {
    return *labels.objects.emplace_back(std::make_unique<Label>(resource_manager.get_font(font_name, height), pos, color, alignment, text));
}
Label& MyApp::push_label(std::unique_ptr<Label>&& obj) { return *labels.objects.emplace_back(std::move(obj)); }

GLFWwindow* MyApp::create_window(const char* title, const unsigned int w, const unsigned int h) {
    GLFWwindow* out;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_X11_CLASS_NAME, "graphics-engine");
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "graphics-engine");

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // clang-format off
    out = glfwCreateWindow(
        w,
        h,
        title,
        nullptr,
        nullptr
    );
    // clang-format on

    if(!out) printf(LOAD_WINDOW_ERROR_MSG);

    return out;
}

MyApp::MyApp(GLFWwindow*&& window, const char* app_title)
    : window(window), title(app_title ? app_title : glfwGetWindowTitle(window)), labels(resource_manager) {
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    camera.set_dimensions(SCR_WIDTH, SCR_HEIGHT);
    // store this instance so static callbacks can access it
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        MyApp*&& app = static_cast<MyApp*>(glfwGetWindowUserPointer(window));
        if(!app) return;
        app->camera.set_dimensions(w, h);
    });
    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// TODO: Input system
void MyApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if(action == GLFW_PRESS)
        printf("Key %d just pressed\n", key);

    if(MyApp*&& p_app = static_cast<MyApp*>(glfwGetWindowUserPointer(window))) {
        if(p_app->labels.objects.size() >= 3) (*std::next(p_app->labels.objects.begin(), 2))->set_text("Key " + std::to_string(key) + " just pressed");
    }
}


void MyApp::run(const std::function<void()>& on_update) {
    // if(!window) init();
    if(!window) printf("MyApp::window == nullptr\n");
    // Player player(SCR_WIDTH, SCR_HEIGHT, window, glm::vec3{100.0f, 200.0f, 0.0f});
    while(!glfwWindowShouldClose(window)) {
        timeNow = glfwGetTime();
        deltaTime = timeNow - lastFrame;
        lastFrame = timeNow;
        if(on_update) on_update();

        // player.update(deltaTime);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        const glm::mat4x4&& VP = camera.get_view_projection();
        labels.draw(VP);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
