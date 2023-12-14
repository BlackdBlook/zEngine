﻿#include "FrameBuffer.h"

#include <glad/glad.h>

FrameBuffer::FrameBuffer(GLsizei sizeX, GLsizei sizeY)
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    glRenderbufferStorage(GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8, sizeX, sizeY);

    // 生成纹理
    
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX,
        sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 将它附加到当前绑定的帧缓冲对象
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D, texColorBuffer, 0);  
    
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8, sizeX, sizeY);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER, rbo);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG("FrameBuffer Init Failed");
        
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindBuffer()
{
    if(CheckBuffer())
    {
        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    }else
    {
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        LOG("FrameBuffer is Vaild");
    }
}

void FrameBuffer::ReleaseBuffer()
{
    glDeleteFramebuffers(1, &framebuffer);
    framebuffer = 0;
    glDeleteRenderbuffers(1, &rbo);
    rbo = 0;
    glDeleteTextures(1, &texColorBuffer);
    texColorBuffer = 0;
}

void FrameBuffer::BindDefaultBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool FrameBuffer::CheckBuffer()
{
    return glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER) ==
        GL_FRAMEBUFFER_COMPLETE;
}
