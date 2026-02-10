#pragma once
#include <cstring>
#include <string_view>
#define SHADER_DIR "engine/assets/shaders/"

// #define FONT_DIR "assets/fonts/"

// TODO: should be const char* instead of enum
// (may even be constexpr - so strings won't exist in binary)
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
