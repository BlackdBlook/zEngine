#pragma once
#include"../../ToolKit/Typedef.h"
#include <map>
#include <glm/glm.hpp>
class Shader;
class ShaderProgram
{
    GLID programID;
    std::map<const char*, GLID>* uniformCache;

    GLID getUniformFromCache(const char* name);


public:
    ShaderProgram();
    ShaderProgram(const char* ver);
    ShaderProgram(const char* ver,const char* far);
    void use();
    void link();
    void Attach(Shader& s);
    void operator+=(Shader& s);
    void setUniform(const char* name,float x);
    void setUniform(const char* name,int x);
    void setUniform(const char* name, const glm::vec3& x);
    void setUniform(const char* name, const glm::mat4& x);
    void setUniform(const char* name, float x, float y, float z);
    void setUniform(const char* name, float x, float y, float z, float w);
    ~ShaderProgram();
};

