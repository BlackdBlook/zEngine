#include "Shader.h"
#include <cstring>
#include "../../ToolKit/FileToolKit.h"
#include <iostream>
const char* defultPath = "Shaders/";

Shader::Shader(const char* name, EShaderType t)
{
    const char* type;
    switch (t)
    {
    case EShaderType::VertexShader:
        type = ".vsc";
        break;
    case EShaderType::FragmentShader:
        type = ".fsc";
        break;
    case EShaderType::CompileShader:
        type = ".csc";
        break;
    default:
        return;
        break;
    }

    id = glCreateShader((GLenum)t);
    std::string path = PathToolKit::CompiePath
    ({ defultPath ,name }) + type;
    std::string s = FileToolKit::ReadFile(path.c_str());
    auto sp = s.c_str();
    GLint lp = (GLint)s.length();
    glShaderSource(id, 1, &sp, &lp);
    glCompileShader(id);

    int  success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "Error : " << name << "\n" << infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteShader(id);
}
