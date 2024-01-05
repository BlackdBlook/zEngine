#pragma once
#include "ToolKit/Typedef.h"

class SceneDepthFrameBuffer
{
    GLID depthMapFBO;
    GLID depthMap;
public:
    SceneDepthFrameBuffer();

    void BindAsFrameBuffer();
    void UnBindAsFrameBuffer();

    void BindAsTexture(int index);
};
