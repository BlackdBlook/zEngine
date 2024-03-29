#pragma once
#include "ToolKit/Typedef.h"

class LightScenceDepthFrameBufferFactory;
class ShaderProgram;

class LightSceneDepthFrameBuffer
{
    friend LightScenceDepthFrameBufferFactory;
    SPtr<ShaderProgram> RenderShader;
    GLID depthMapFBO;
    GLID depthMap;
public:
    LightSceneDepthFrameBuffer();

    void BindAsFrameBuffer();
    void UnBindAsFrameBuffer();
    int GetShadowMapTextureId();
    void BindAsTexture();
    void BindAsTexture(int index);

    void RenderToScreen();
};
