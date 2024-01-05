#include "SceneDepthFrameBuffer.h"

#include "Engine/zEngine.h"

SceneDepthFrameBuffer::SceneDepthFrameBuffer()
{
    
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                 (GLsizei)Engine::WindowX, (GLsizei)Engine::WindowY,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    int count = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &count);

    LOG("Max Texture unit count : ", count);
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
