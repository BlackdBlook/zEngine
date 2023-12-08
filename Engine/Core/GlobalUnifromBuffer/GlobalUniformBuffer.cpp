#include "GlobalUniformBuffer.h"

#include "Header.h"
#include "Engine/Core/ShaderProgram.h"
#include "Engine/Core/Camera/Camera.h"

void GlobalUniformBuffer::RegistUniformBlock(ShaderProgram* program)
{
    std::vector<std::string> ss;
    program->GetAllUniformBlockName(ss);

    for (auto& s : ss)
    {
        UniformBufferInfo info;
        GLID block = glGetUniformBlockIndex(
            program->getProgramID(), s.c_str());
        auto UniformBlockMapCache = UniformBlockMap.find(s);
        if (UniformBlockMapCache == UniformBlockMap.end())
        {

            glGetActiveUniformBlockiv(program->getProgramID(), block,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &info.size);

            glGenBuffers(1, &info.uniformBufferID);
            glBindBuffer(GL_UNIFORM_BUFFER, info.uniformBufferID);
            glBufferData(GL_UNIFORM_BUFFER, info.size, nullptr, GL_STATIC_DRAW);


            LOG("Create New Uniform Buffer:", s, "ID:", info.uniformBufferID);
            info.BindPort = (GLuint)UniformBlockMap.size();
            glBindBufferBase(GL_UNIFORM_BUFFER,
                info.BindPort, info.uniformBufferID);

            RetrySetOperation(s, info.uniformBufferID);
            UniformBlockMap.insert({s, std::move(info)});
        }
        else
        {
            GLsizei size;

            glGetActiveUniformBlockiv(program->getProgramID(), block,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &size);

            if (UniformBlockMapCache->second.size != size)
            {
                LOG("Error: Uniform Size Not Match", s);
            }
            info = UniformBlockMapCache->second;
        }
        LOG("Bind Uniform", s, program->GetName(), info.BindPort);
        glUniformBlockBinding(program->getProgramID(),
            block, info.BindPort);
    }
}

void GlobalUniformBuffer::RetrySetOperation(const std::string& name, GLID buffer)
{
    auto m = MissingBufferSetOperationCache.find(name);
    if(m == MissingBufferSetOperationCache.end())
    {
        return;
    }

    glBindBuffer(GL_UNIFORM_BUFFER,buffer);
    SetUniformCommand& c = m->second;
    glBufferSubData(GL_UNIFORM_BUFFER, c.Offset, c.Data.size(), c.Data.data());
    c.Data = std::vector<uint8>(c.Data.size(), 0);
    LOG(__func__, name, c.name);

#ifdef CHECK_BUFFER_BLOCK
    
    glGetBufferSubData(GL_UNIFORM_BUFFER, c.Offset, c.Data.size(), c.Data.data());

    LOG(c.Offset);
    LOG(*(glm::mat4*)c.Data.data());
    LOG(Camera::GetCamera()->GetCameraProjection());
    
#endif
    MissingBufferSetOperationCache.erase(name);
}

GlobalUniformBuffer* GlobalUniformBuffer::GetInstance()
{
    static GlobalUniformBuffer ins;

    return &ins;
}
