#pragma once
#include "Header.h"
#include "Engine/zEngine.h"

class FrameBuffer
{
    friend class zEngine;
    static FrameBuffer* CurrentFrameBuffer;
    
    void ReleaseBuffer();

    GLID texColorBuffer;
    GLID framebuffer;
    GLID rbo;
    
public:

    FrameBuffer(GLsizei sizeX, GLsizei sizeY);

    ~FrameBuffer();

    void BindBuffer();
    
    bool CheckBuffer();

    GLID GetBufferTexture()
    {
        return texColorBuffer;
    }

    static void BindDefaultBuffer();
};
