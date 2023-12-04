#include "ShaderProgram.h"
#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include "../../Header.h"

GLID ShaderProgram::getUniformFromCache(const std::string& name)
{
    glUseProgram(programID);
    auto value = uniformCache.find(name);
    if (value == uniformCache.end())
    {
        GLID ans;
        ans = glGetUniformLocation(programID, name.c_str());
        if (ans == 0xffffffff)
        {
            LOG("unifrom not find", shaderNameVer, shaderNameFar, name);
        }
        uniformCache.insert(std::pair<std::string, GLID>(name, ans));
        return ans;
    }
    else
    {
        return value->second;
    }
}

void ShaderProgram::showAllActiveUnifrom()
{
    GLint maxUniformLen;
    GLint numUniforms;
    char* uniformName;
    GLint index;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);
    glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH,
                   &maxUniformLen);
    uniformName = (char*)malloc(sizeof(char) * maxUniformLen);
    for (index = 0; index < numUniforms; index++)
    {
        GLint size;
        GLenum type;
        // Get the uniform info
        glGetActiveUniform(programID, index, maxUniformLen, NULL,
            &size, &type, uniformName);
        std::string s = uniformName;
        LOG("unifroms:", s);
    }
    free(uniformName);
}

ShaderProgram::ShaderProgram()
{
    programID = glCreateProgram();
}

ShaderProgram::ShaderProgram(ShaderProgram&& other)
    noexcept
{
    programID = other.programID;
    shaderNameVer = std::move(other.shaderNameVer);
    shaderNameFar = std::move(other.shaderNameFar);
    // 拷贝和移动时放弃缓存
    //uniformCache = std::move(other.uniformCache);
}

ShaderProgram::ShaderProgram(const ShaderProgram& other)
{
    programID = other.programID;
    shaderNameVer = other.shaderNameVer;
    shaderNameFar = other.shaderNameFar;
    // 拷贝和移动时放弃缓存
    //uniformCache = other.uniformCache;
}

ShaderProgram::ShaderProgram(std::string&& ver)
{
    programID = glCreateProgram();
    shaderNameVer = ver;
    shaderNameFar = shaderNameVer;
    use();
    Shader vs(shaderNameVer, EShaderType::VertexShader);
    Shader fs(shaderNameFar, EShaderType::FragmentShader);

    Attach(vs);
    Attach(fs);
    link();

    //showAllActiveUnifrom();
}

ShaderProgram::ShaderProgram(std::string&& ver, std::string&& far)
{
    programID = glCreateProgram();
    shaderNameVer = ver;
    shaderNameFar = far;
    use();
    Shader vs(shaderNameVer, EShaderType::VertexShader);
    Shader fs(shaderNameFar, EShaderType::FragmentShader);

    Attach(vs);
    Attach(fs);
    link();
    //showAllActiveUnifrom();
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
    glUniformMatrix4fv(id, 1,GL_FALSE, glm::value_ptr(x));

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
    glDeleteProgram(programID);
}
