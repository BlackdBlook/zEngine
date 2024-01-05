#include "RenderCommandQueue.h"

#include "Header.h"
#include "Engine/Core/Camera/Camera.h"

#define INSTANCE (RenderCommandQueue::GetInstance())

void RenderCommandQueue::EnqueueCommand(RenderCommand&& command)
{
    INSTANCE.commands.Enqueue(std::move(command));
}

void RenderCommandQueue::Flush()
{
    INSTANCE.FlushImpl();
}

void RenderCommandQueue::FlushImpl()
{
    // RenderShadow();
    // RenderScene();
    commands.Empty();
}

void RenderCommandQueue::ExecuteCommand(RenderCommand& command)
{
    if(!command.IsVaild())
    {
        LOG("Error An Invalid RenderCommand", command.Shader->GetName());
        return;
    }
    // LOG("Draw", tempCommand.Shader->GetName());

    if(command.PreExcute != nullptr)
    {
        command.PreExcute(&command);
    }

    command.Excute();

    if(command.PostExcute != nullptr)
    {
        command.PostExcute(&command);
    }
}

void RenderCommandQueue::RenderShadow()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    commands.ForLoop([this](RenderCommand& c)
    {
        c.ExcuteByShadowPass(ShadowPass.get());
    });
    // glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RenderCommandQueue::RenderScene()
{
    std::multimap<float, RenderCommand> OpaqueTemp;
    std::multimap<float, RenderCommand> TranslucentTemp;
    const auto pos = Camera::GetCamera()->GetPos();
    
    while(!commands.IsEmpty())
    {
        RenderCommand tempCommand;
        commands.Dequeue(tempCommand);

        if(tempCommand.Shader->BlendType == BlendType::Skybox)
        {
            ExecuteCommand(tempCommand);
        }else if(tempCommand.Shader->BlendType == BlendType::Opaque)
        {
            float dis = glm::length(tempCommand.TargetObject->GetPos() - pos);
            OpaqueTemp.insert({dis, std::move(tempCommand)});
        }else if(tempCommand.Shader->BlendType == BlendType::Translucent)
        {
            float dis = glm::length(tempCommand.TargetObject->GetPos() - pos);
            TranslucentTemp.insert({dis, std::move(tempCommand)});
        }
        
    }

    // 不透明从前往后
    for(auto i = OpaqueTemp.begin();i != OpaqueTemp.end();++i)
    {
        RenderCommand& tempCommand = i->second;
        
        ExecuteCommand(tempCommand);
    }

    // 半透明从后往前
    for(auto i = TranslucentTemp.rbegin();i != TranslucentTemp.rend();++i)
    {
        RenderCommand& tempCommand = i->second;
        
        ExecuteCommand(tempCommand);
    }
}

void RenderCommandQueue::ClearQueue()
{
    commands.Empty();
}

RenderCommandQueue::RenderCommandQueue()
{
    ShadowPass = NewSPtr<ShaderProgram>("ShadowMap");
    GLfloat near_plane = 1.0f, far_plane = 17.5f;
    glm::mat4 lightProjection =
        glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(
        glm::vec3(-5.0f, 2.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    ShadowPass->setUniform("lightSpaceMatrix", lightSpaceMatrix);
}

RenderCommandQueue& RenderCommandQueue::GetInstance()
{
    static RenderCommandQueue ans;
    return ans;
}
