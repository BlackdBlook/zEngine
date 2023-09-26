#include "ShaderProgram.h"
#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include "../../Header.h"
GLID ShaderProgram::getUniformFromCache(const std::string& name)
{
    glUseProgram(programID);
    auto value = uniformCache->find(name);
    if (value == uniformCache->end())
    {
        GLID ans;
        ans = glGetUniformLocation(programID, name.c_str());
        if (ans == 0xffffffff)
        {
            LOG("unifrom not find", shaderNameVer, shaderNameFar, name);
        }
        uniformCache->insert(std::pair<std::string, GLID>(name, ans));
        return ans;
    }
    else
    {
        return value->second;
    }
    
}

ShaderProgram::ShaderProgram()
{
    programID = glCreateProgram(); 
    uniformCache = new std::unordered_map<std::string, GLID>();
}

ShaderProgram::ShaderProgram(std::string&& ver)
{
    programID = glCreateProgram();
    uniformCache = new std::unordered_map<std::string, GLID>();
    shaderNameVer = ver;
    shaderNameFar = shaderNameVer;
    use();
    Shader vs(shaderNameVer, EShaderType::VertexShader);
    Shader fs(shaderNameFar, EShaderType::FragmentShader);
    
    Attach(vs);
    Attach(fs);
    link();
}

ShaderProgram::ShaderProgram(std::string&& ver, std::string&& far)
{
    programID = glCreateProgram();
    uniformCache = new std::unordered_map<std::string, GLID>();
    shaderNameVer = ver;
    shaderNameFar = far;
    use();
    Shader vs(shaderNameVer, EShaderType::VertexShader);
    Shader fs(shaderNameFar, EShaderType::FragmentShader);
    
    Attach(vs);
    Attach(fs);
    link();
}

void ShaderProgram::use()
{
    glUseProgram(programID);
}

void ShaderProgram::link()
{
    glLinkProgram(programID);
}

void ShaderProgram::Attach(Shader& vs)
{
    if (*vs == 0)
    {
        std::cout << "Error\n";
        return;
    }
    glAttachShader(programID, *vs);
    glCheckError();
}

void ShaderProgram::operator+=(Shader& s)
{
    Attach(s);
}

void ShaderProgram::setUniform(const char* name, float x)
{
    GLID id = getUniformFromCache(name);
    
    glUniform1f(id, x);

    glCheckError(name);
}

void ShaderProgram::setUniform(const char* name, int x)
{
    GLID id = getUniformFromCache(name);
    glUniform1i(id, x);

    glCheckError(name);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& x)
{
    setUniform(name, x.x, x.y, x.z);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& x)
{
    GLID id = getUniformFromCache(name);
    glUniformMatrix4fv(id, 1,GL_FALSE,glm::value_ptr(x));

    glCheckError(name);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
    GLID id = getUniformFromCache(name);
    glUniform3f(id, x, y, z);
    
    glCheckError(name);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z, float w)
{
    GLID id = getUniformFromCache(name);
    glUniform4f(id, x, y, z, w);

    glCheckError(name);
}

ShaderProgram::~ShaderProgram()
{
    delete uniformCache;
    glDeleteProgram(programID);
}
