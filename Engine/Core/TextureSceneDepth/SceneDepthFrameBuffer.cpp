#include "SceneDepthFrameBuffer.h"

#include "Engine/zEngine.h"
#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"
#include "ToolKit/GLLib.h"

SceneDepthFrameBuffer::SceneDepthFrameBuffer()
{
    
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                 (GLsizei)Engine::WindowX * 2, (GLsizei)Engine::WindowY * 2,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    GLfloat near_plane = 10.0f, far_plane = 25.5f;
    lightProjection = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);
    
    lightView = glm::lookAt(glm::vec3{-5.0f, 14.0f, -1.0f}, glm::vec3(0.0f),
        glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    
    SetGlobalUniformBuffer("Matrices","lightSpaceMatrix",
        lightSpaceMatrix);
}

void SceneDepthFrameBuffer::BindAsTexture(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D,depthMap);
}

void SceneDepthFrameBuffer::BindAsFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
}

void SceneDepthFrameBuffer::UnBindAsFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int SceneDepthFrameBuffer::GetShadowMapTextureId()
{
    return GLLib::GetMaxTextureUnitCount() - 1;
}

void SceneDepthFrameBuffer::BindAsTexture()
{
    glActiveTexture(GL_TEXTURE0 + GetShadowMapTextureId());
    glBindTexture(GL_TEXTURE_2D,depthMap);
}

GLID GENVAO()
{
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        0.5f,  1.0f,  0.0f, 1.0f,//左上
        0.5f, 0.5f,  0.0f, 0.0f,//左下 
         1.0f, 0.5f,  1.0f, 0.0f,//右下

        0.5f,  1.0f,  0.0f, 1.0f,//左上
         1.0f, 0.5f,  1.0f, 0.0f,//右下
         1.0f,  1.0f,  1.0f, 1.0f //右上
    };
    GLID VAO;
    // screen quad VAO
    unsigned int quadVBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    return VAO;
}

void SceneDepthFrameBuffer::RenderToScreen()
{
    static GLID Vao = GENVAO();
    if(RenderShader == nullptr)
    {
        RenderShader = NewSPtr<ShaderProgram>("ShowFrameBuffer");
    }
    
    RenderShader->use();
    glActiveTexture(GL_TEXTURE0);   
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glBindVertexArray(Vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}