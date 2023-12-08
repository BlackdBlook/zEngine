#pragma once
#include"../../ToolKit/Typedef.h"
#include <map>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

enum class BlendType
{
    Opaque,
    Translucent,
    Mask,
};

enum class BlendType;
class Shader;
class ShaderProgram
{
    GLID programID;
    std::unordered_map<std::string, GLID> uniformCache;

    GLID getUniformFromCache(const std::string& name);

    void showAllActiveUnifrom();

    std::string shaderNameVer;
    std::string shaderNameFar;

    void link();
    void Attach(Shader& s);

public:
    BlendType BlendType = BlendType::Opaque;
    std::string GetName();
    void use();
    ShaderProgram();
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram(const ShaderProgram& other);
    ShaderProgram(std::string&& ver);
    ShaderProgram(std::string&& ver,std::string&& far);
    void operator+=(Shader& s);
    void setUniform(const char* name,float x);
    void setUniform(const char* name,int x);
    void setUniform(const char* name, const glm::vec3& x);
    void setUniform(const char* name, const glm::mat4& x);
    void setUniform(const char* name, float x, float y, float z);
    void setUniform(const char* name, float x, float y, float z, float w);
    ~ShaderProgram();
};

