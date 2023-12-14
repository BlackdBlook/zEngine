#include "GlobalUniformBuffer.h"

#include "Header.h"
#include "Engine/Core/ShaderProgram.h"
#include "Engine/Core/Camera/Camera.h"

void GlobalUniformBuffer::RegistUniformBlock(ShaderProgram* program)
{
    std::vector<std::string> ss;
    program->GetAllUniformBlockName(ss);
    const GLID programID = program->getProgramID();
    GLID BindPort = -1;
    for (auto& s : ss)
    {
        
        // 获取块索引
        GLID blockIndex = glGetUniformBlockIndex(
            program->getProgramID(), s.c_str());
        auto UniformBlockMapCache = UniformBlockMap.find(s);
        if (UniformBlockMapCache == UniformBlockMap.end())
        {
            UniformBufferInfo info;
            // 获取块大小
            glGetActiveUniformBlockiv(programID, blockIndex,
                GL_UNIFORM_BLOCK_DATA_SIZE, &info.size);
            // 获取成员名和偏移
            {
                GLint numUniforms;
                glGetActiveUniformBlockiv(programID, blockIndex,
                    GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms);

                GLuint* uniformIndices = new GLuint[numUniforms];
                glGetActiveUniformBlockiv(programID, blockIndex,
                    GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)uniformIndices);


                for (GLint i = 0; i < numUniforms; ++i) {
                    char uniformName[256];
                    glGetActiveUniformName(programID, uniformIndices[i],
                        sizeof(uniformName), NULL, uniformName);

                    GLint size;
                    glGetActiveUniformsiv(programID, 1, &uniformIndices[i],
                        GL_UNIFORM_SIZE, &size);

                    GLenum type;
                    glGetActiveUniformsiv(programID, 1, &uniformIndices[i],
                        GL_UNIFORM_TYPE, (GLint*)&type);
                    
                    GLint offset;
                    glGetActiveUniformsiv(programID, 1, &uniformIndices[i],
                        GL_UNIFORM_OFFSET, &offset);

                    // LOG("Uniform ",uniformName," has offset ",offset,"\n");
                    info.offsetMap.insert({
                        std::string(uniformName),
                        {type, size, offset}
                    });
                }
                delete[] uniformIndices;
            }

            
            glGenBuffers(1, &info.uniformBufferID);
            glBindBuffer(GL_UNIFORM_BUFFER, info.uniformBufferID);
            glBufferData(GL_UNIFORM_BUFFER, info.size, nullptr, GL_STATIC_DRAW);

            LOG("Create New Uniform Buffer:", s, "ID:", info.uniformBufferID);
            info.BindPort = (GLuint)UniformBlockMap.size();
            BindPort = info.BindPort;
            glBindBufferBase(GL_UNIFORM_BUFFER,
                info.BindPort, info.uniformBufferID);
            RetrySetOperation(s, info);
            UniformBlockMap.insert({s, std::move(info)});
        }
        else
        {
            GLsizei size;

            glGetActiveUniformBlockiv(program->getProgramID(), blockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &size);

            if (UniformBlockMapCache->second.size != size)
            {
                LOG("Error: Uniform Size Not Match", s);
            }
            BindPort = UniformBlockMapCache->second.BindPort;
        }
        LOG("Bind Uniform", s, program->GetName(), BindPort);
        glUniformBlockBinding(program->getProgramID(),
            blockIndex, BindPort);
    }
}

void GlobalUniformBuffer::RetrySetOperation(const std::string& name,
    const UniformBufferInfo& info)
{
    auto m = MissingBufferSetOperationCache.find(name);
    if(m == MissingBufferSetOperationCache.end())
    {
        return;
    }

    glBindBuffer(GL_UNIFORM_BUFFER,info.uniformBufferID);
    for(SetUniformCommand& c : m->second)
    {
        if(c.memberName == nullptr)
        {
            glBufferSubData(GL_UNIFORM_BUFFER,
                c.Offset,
                c.Data.size(), c.Data.data());
        }else
        {
            glBufferSubData(GL_UNIFORM_BUFFER,
                info.offsetMap.find(c.memberName)->second.offset,
                c.Data.size(), c.Data.data());
        }
    }

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
