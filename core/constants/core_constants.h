#pragma once
#include <cstring>
#include <glm/glm.hpp>
#include <string_view>
#define SHADER_DIR "core/assets/shaders/"

// #define FONT_DIR "assets/fonts/"

namespace GPE
{
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
}  // namespace GPE
enum class TextureUnits : unsigned char
{
    GENERAL0 = 0,
    GENERAL1 = 1,
    FONT_ATLAS = 3,
    TextureUnits_MAX = 16,
};

enum class ShaderID
{
    TEXT
};

struct ShadersPaths
{
    const std::string_view vertex;
    const std::string_view fragment;
    const std::string_view geometry;
    constexpr ShadersPaths(const std::string_view& vertex, const std::string_view& fragment,
                           const std::string_view& geometry = "")
        : vertex(vertex), fragment(fragment), geometry(geometry)
    {
    }
    template <enum ShaderID>
    constexpr static const ShadersPaths get_path()
    {
        // default (unknown)
        return ShadersPaths{"text.vs", "text.fs", nullptr};
    }
};

// TODO: add SHADER_DIR "/" in ResourceManager
#define _SHADER2(ID, vertpath, fragpath)                                \
    template <>                                                         \
    constexpr const ShadersPaths ShadersPaths::get_path<ShaderID::ID>() \
    {                                                                   \
        return ShadersPaths{vertpath, fragpath};                        \
    }
#define _SHADER3(ID, vertpath, fragpath, geompath)                      \
    template <>                                                         \
    constexpr const ShadersPaths ShadersPaths::get_path<ShaderID::ID>() \
    {                                                                   \
        return ShadersPaths{vertpath, fragpath, geompath};              \
    }

#pragma region list_shaders
_SHADER2(TEXT, "text.vs", "text.fs")
#pragma endregion

#undef _SHADER2
#undef _SHADER3
