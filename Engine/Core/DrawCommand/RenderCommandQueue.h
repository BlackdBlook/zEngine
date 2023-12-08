#pragma once
#include "RenderCommand.h"
#include "ToolKit/Queue.h"

class RenderCommandQueue
{
public:
    friend class zEngine;
    
    static void EnqueueCommand(RenderCommand&& command);

    template<typename Task>
    static void EnqueueCommandTask(Task task)
    {
        RenderCommand tmp;
        task(tmp);
        EnqueueCommand(std::move(tmp));
    }

    
private:

    static void Flush();
    void FlushImpl();
    void ExecuteCommand(RenderCommand& command);

    
    RenderCommandQueue();
    TQueue<RenderCommand> commands;
    static RenderCommandQueue& GetInstance();
};

using RenderQueue = RenderCommandQueue;

#define PushRenderCommand RenderQueue::EnqueueCommandTask

/* Exampal

PushRenderCommand([this](RenderCommand& command)
{
    command.vao = vao;
    command.Shader = shader.get();
    command.Textures.push_back(&Tex1);
    command.Textures.push_back(&Tex2);
});
 
 */