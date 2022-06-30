#include "ShaderProgram.h"
#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include "../../Header.h"
GLID ShaderProgram::getUniformFromCache(const char* name)
{
    glUseProgram(programID);
    auto value = uniformCache->find(name);
    if (value == uniformCache->end())
    {
        GLID ans;
        ans = glGetUniformLocation(programID, name);
        if (ans == 0xffffffff)
        {
            LOG("unifrom not find", programID, name);
        }
        uniformCache->insert(std::pair<const char*, GLID>(name, ans));
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
    uniformCache = new std::map<const char*, GLID>();
}

ShaderProgram::ShaderProgram(const char* ver, const char* far)
{
    programID = glCreateProgram();
    uniformCache = new std::map<const char*, GLID>();
    use();
    Shader vs(ver, EShaderType::VertexShader);
    Shader fs(far, EShaderType::FragmentShader);
    
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
}

void ShaderProgram::operator+=(Shader& s)
{
    Attach(s);
}

void ShaderProgram::setUniform(const char* name, float x)
{
    GLID id = getUniformFromCache(name);
    
    glUniform1f(id, x);
}

void ShaderProgram::setUniform(const char* name, int x)
{
    GLID id = getUniformFromCache(name);
    glUniform1i(id, x);
}

void ShaderProgram::setUniform(const char* name, glm::vec3& x)
{
    setUniform(name, x.x, x.y, x.z);
}

void ShaderProgram::setUniform(const char* name, glm::mat4& x)
{
    GLID id = getUniformFromCache(name);
    glUniformMatrix4fv(id, 1,GL_FALSE,glm::value_ptr(x));
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
    GLID id = getUniformFromCache(name);
    glUniform3f(id, x, y, z);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z, float w)
{
    GLID id = getUniformFromCache(name);
    glUniform4f(id, x, y, z, w);
}

ShaderProgram::~ShaderProgram()
{
    delete uniformCache;
    glDeleteProgram(programID);
}
