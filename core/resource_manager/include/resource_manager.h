#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <constants.h>
#include <font.h>
#include <shader.h>

#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

inline constexpr decltype(std::ignore) preload{};

class ResourceManager {
public:
    using ShaderKey = ShaderID;
    using FontKey = std::pair<std::string, const unsigned int>;

private:
    std::map<ShaderKey, std::shared_ptr<Shader> > shaders;
    std::map<FontKey, std::shared_ptr<FontAtlas> > fonts;
    const char* _shaders_dir = nullptr;
    const char* _font_dir = nullptr;

public:
    template <ShaderKey key>
    [[nodiscard("Are you preloading resources? Use preload = get_shader<>() then")]]
    std::shared_ptr<Shader> get_shader() {
        // TODO: constexpr string concatenation OR using std::filesystem::path
        using std::string;
        auto& ptr = shaders[key];
        if(!ptr) {
            ShadersPaths paths = ShadersPaths::get_path<key>();
            if(_shaders_dir) {
                string vertex = string(_shaders_dir) + '/' + string(paths.vertex);
                string fragment = string(_shaders_dir) + '/' + string(paths.fragment);
                if(!paths.geometry.empty()) {
                    string geometry = (string(_shaders_dir)) + '/' + string(paths.geometry);
                    ptr = std::make_shared<Shader>(vertex.c_str(), fragment.c_str(), geometry.c_str());
                } else
                    ptr = std::make_shared<Shader>(vertex.c_str(), fragment.c_str());
            } else
                ptr = std::make_shared<Shader>(paths.vertex, paths.fragment, paths.geometry);
        }
        return ptr;
    }
    [[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
    std::shared_ptr<FontAtlas> get_font(const std::string_view& name, const unsigned int size = 12);

    ResourceManager(const char* shaders_dir = "core/assets/shaders/", const char* font_dir = "core/assets/fonts/");
};
#endif
