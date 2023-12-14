#pragma once
#include "Header.h"

class FrameBuffer
{

    void ReleaseBuffer();

    unsigned int texColorBuffer;
    GLID framebuffer;
    GLID rbo;
    
public:

    FrameBuffer(GLsizei sizeX, GLsizei sizeY);

    void BindBuffer();
    
    bool CheckBuffer();

    static void BindDefaultBuffer();
};
