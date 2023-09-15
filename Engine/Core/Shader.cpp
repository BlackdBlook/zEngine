#include "Shader.h"
#include <cstring>
#include "../../ToolKit/FileToolKit.h"
#include <iostream>

#include "../SubSystem/AssetSystem.h"
const char* defultPath = "Shaders/";

Shader::Shader(const char* name, EShaderType t)
{
    //const char* type = nullptr;
    std::string FullName{name};
    switch (t)
    {
    case EShaderType::VertexShader:
        FullName += ".vsc";
        break;
    case EShaderType::FragmentShader:
        FullName += ".fsc";
        break;
    case EShaderType::CompileShader:
        FullName += ".csc";
        break;
    }

    id = glCreateShader((GLenum)t);
    //std::string path = PathToolKit::CompiePath({ defultPath ,name }) + type;
    std::string path = AssetSystem::GetInstance()->GetFilePathByName(FullName);
    std::string s = FileToolKit::ReadFile(path.c_str());
    auto sp = s.c_str();
    GLint lp = (GLint)s.length();
    glShaderSource(id, 1, &sp, &lp);
    glCompileShader(id);

    int success;
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
