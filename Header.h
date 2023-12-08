#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ToolKit/Typedef.h"
#include "ToolKit/ImgToolKit.h"
#include "ToolKit/FileToolKit.h"
#include "LogPrinter/Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Engine/Core/ShaderProgram.h"
#include <functional>
#include "Engine/Core/Texture2D/Texture2D.h"

#define MAT4(name) glm::mat4 name(1.0f)
#define LOG(...) Log::NameSpacePrinter(__FILE__, __LINE__, __VA_ARGS__)
#define VEC3_ZERO glm::vec3(0,0,0)

template<typename ...T>
GLenum glCheckError_(const char *file, int line, T ... args)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            default:break;
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;

        Log::printer(args...);
    }
    return errorCode;
}
inline GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        default:break;
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#ifdef CheckError
#define glCheckError(...) glCheckError_(__FILE__, __LINE__, __VA_ARGS__)
#else
#define glCheckError(...)
#endif