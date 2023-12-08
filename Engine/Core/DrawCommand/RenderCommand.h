#pragma once
#include <functional>
#include <vector>
#include <glm/vec3.hpp>

#include "ToolKit/Typedef.h"

class Texture2D;
class ShaderProgram;

enum class DrawType : uint8
{
    None,
    DrawArrays,
    DrawElements,
};

class RenderCommand
{
public:
    RenderCommand();

    RenderCommand(const RenderCommand& other) = delete;

    RenderCommand(RenderCommand&& other) = default;

    RenderCommand& operator=(RenderCommand&& other) noexcept = default;

    virtual std::string GetName();

    DrawType DrawType = DrawType::None;

    ShaderProgram* Shader = nullptr;

    GLID vao = 0;

    GLsizei vertexNum = 0;

    glm::vec3 WorldPos {0};

    std::vector<Texture2D*> Textures;

    std::function<void(RenderCommand*)> PreExcute = {};
    
    std::function<void(RenderCommand*)> PostExcute = {};
    
    virtual void Excute();

    virtual bool IsVaild();

    virtual ~RenderCommand() = default;
};
