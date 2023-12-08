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
    std::multimap<float, RenderCommand> Temp;
    const auto pos = Camera::GetCamera()->GetPos();
    // LOG("sort start");
    while(!commands.IsEmpty())
    {
        RenderCommand tempCommand;
        commands.Dequeue(tempCommand);

        if(tempCommand.Shader->BlendType != BlendType::Translucent)
        {
            ExecuteCommand(tempCommand);
        }
        float dis = glm::length(tempCommand.WorldPos - pos);
        Temp.insert({dis, std::move(tempCommand)});
    }

    for(auto i = Temp.rbegin();i != Temp.rend();++i)
    {
        RenderCommand& tempCommand = i->second;
        
        ExecuteCommand(tempCommand);
    }
    
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

RenderCommandQueue::RenderCommandQueue()
{
    
}

RenderCommandQueue& RenderCommandQueue::GetInstance()
{
    static RenderCommandQueue ans;
    return ans;
}
