#ifndef RESOURCE_MANAGER_CPP
#define RESOURCE_MANAGER_CPP
#include <resource_manager.h>
#include <shader.h>

#include <string>

[[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
std::shared_ptr<FontAtlas> ResourceManager::get_font(const std::string_view& name, const unsigned int size) {
    const std::string&& path = _font_dir ? (std::string(_font_dir) + '/' + name.data()) : std::string(name);
    std::shared_ptr<FontAtlas>& ptr = fonts[{path, size}];
    if(!ptr) ptr = std::make_shared<FontAtlas>(path.c_str(), size);
    return ptr;
}


ResourceManager::ResourceManager(const char* shaders_dir, const char* font_dir) : _shaders_dir(shaders_dir), _font_dir(font_dir) {}
#endif
