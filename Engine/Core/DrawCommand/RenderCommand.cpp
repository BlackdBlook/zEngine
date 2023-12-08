#include "RenderCommand.h"

#include "Engine/Core/ShaderProgram.h"
#include "Engine/Core/Texture2D/Texture2D.h"

RenderCommand::RenderCommand()
{
    vao = 0;
}

std::string RenderCommand::GetName()
{
    if(Shader)
    {
        return Shader->GetName();
    }else
    {
        return "None Shader attached";
    }
}

void RenderCommand::Excute()
{
    Shader->use();

    uint8 ti = 0;
    for(auto t : Textures)
    {
        t->Bind(ti);
        ++ti;
    }
    
    glBindVertexArray(vao);
    switch (DrawType)
    {
    case DrawType::DrawArrays:
        glDrawArrays(GL_TRIANGLES, 0, vertexNum);
        break;
    case DrawType::DrawElements:
        glDrawElements(GL_TRIANGLES, vertexNum, GL_UNSIGNED_INT, nullptr);
        break;
    case DrawType::None:
    default:
        LOG("Render Command Error: None Draw Type");
    }
}

bool RenderCommand::IsVaild()
{
    if(DrawType == DrawType::None)
    {
        return false;
    }

    if(Shader == nullptr)
    {
        return false;
    }

    if(vao == 0)
    {
        return false;
    }

    if(vertexNum == 0)
    {
        return false;
    }
    
    return true;
}
