#pragma once
#include <set>
#include <unordered_map>

#include "Header.h"
#include "ToolKit/Typedef.h"

class ShaderProgram;

struct UniformBufferInfo
{
    GLsizei size;
    GLID uniformBufferID;
    GLID BindPort;
    UniformBufferInfo() = default;
    UniformBufferInfo& operator=(const UniformBufferInfo& other)
    {
        size = other.size;
        uniformBufferID = other.uniformBufferID;
        BindPort = other.BindPort;
        return *this;
    }
    UniformBufferInfo(const UniformBufferInfo& other)
    {
        size = other.size;
        uniformBufferID = other.uniformBufferID;
        BindPort = other.BindPort;
    }
    UniformBufferInfo(UniformBufferInfo&& other) noexcept
    {
        size = other.size;
        uniformBufferID = other.uniformBufferID;
        BindPort = other.BindPort;
    }
};

struct SetUniformCommand
{
    std::string name;
    GLintptr Offset;
    std::vector<uint8> Data;
    SetUniformCommand() = default;
    SetUniformCommand(const SetUniformCommand& other) = delete;

    SetUniformCommand(SetUniformCommand&& other) noexcept
    {
        name = std::move(other.name);
        Offset = other.Offset;
        Data = std::move(other.Data);
    }
};

class GlobalUniformBuffer
{
    std::unordered_map<std::string, UniformBufferInfo> UniformBlockMap {};

    std::unordered_map<std::string, SetUniformCommand> MissingBufferSetOperationCache;
public:

    void RegistUniformBlock(ShaderProgram* program);

    template<typename T>
    void SetUniformBuffer(const char* Name,T* Data, GLintptr Offset)
    {
        auto target = UniformBlockMap.find(Name);
        if(target == UniformBlockMap.end())
        {
            LOG("Error Uniform Buffer Not Find:", Name);
            CacheMissingBufferSetOperation<T>(Name, Data, Offset);
            return;
        }

        // if(target->second.size != sizeof(T))
        // {
        //     LOG("Error Uniform Buffer Size Not Match",
        //         Name, target->second.size, sizeof(T));
        //     return;
        // }
        glBindBuffer(GL_UNIFORM_BUFFER,
            target->second.uniformBufferID);
        glBufferSubData(GL_UNIFORM_BUFFER, Offset, sizeof(T), Data);
    }
    
    template<typename T>
    void CacheMissingBufferSetOperation(const char* Name,void* Data, GLintptr Offset)
    {
        SetUniformCommand command;
        command.name = std::string{Name};
        command.Offset = Offset;
        size_t s = sizeof(T);
        command.Data = std::vector<uint8>(s);
        memcpy(command.Data.data(), Data, sizeof(T));
        MissingBufferSetOperationCache.insert({Name, std::move(command)});
    }

    void RetrySetOperation(const std::string& name, GLID buffer);

    static GlobalUniformBuffer* GetInstance();
};

template<typename T>
static void SetGlobalUniformBuffer(const char* Name,T& Data, GLintptr Offset = 0)
{
    GlobalUniformBuffer::GetInstance()->SetUniformBuffer(Name, &Data, Offset);
}
