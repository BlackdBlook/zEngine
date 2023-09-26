#pragma once
#include "../../Header.h"

enum class EShaderType : GLenum
{
    VertexShader = 0x8B31,
    FragmentShader = 0x8B30,
    CompileShader = 0x91B9
};
class Shader
{
private:
    GLID id = 0;
public:
    Shader(const std::string& name, EShaderType t);
    GLID operator*() 
    {
        return id;
    }
    ~Shader();
};

