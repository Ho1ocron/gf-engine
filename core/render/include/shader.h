#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <string_view>


class Shader {
    unsigned int ID;

public:
    // uniforms
    void setBool(const char* name,const bool value) const;
    void setInt(const char* name, const int value) const;
    void setFloat(const char* name, const float value) const;
    void setVec2(const char* name, const glm::vec2 &value) const;
    void setVec3(const char* name, const glm::vec3 &value) const;
    void setVec4(const char* name, const glm::vec4 &value) const;
    void setMat2(const char* name, const glm::mat2 &mat) const;
    void setMat3(const char* name, const glm::mat3 &mat) const;
    void setMat4(const char* name, const glm::mat4 &mat) const;
    // use the shader before rendering
    void use() const;

public:
    // Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr);
    Shader(const std::string_view& vertexPath, const std::string_view& fragmentPath, const std::string_view& geometryPath = "");

public:
    unsigned int getId() const { return ID; }
};
#endif
