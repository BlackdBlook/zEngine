#pragma once
#include "ToolKit/Typedef.h"

class ShaderProgram;

class SceneDepthFrameBuffer
{
    SPtr<ShaderProgram> RenderShader;
    GLID depthMapFBO;
    GLID depthMap;
public:
    SceneDepthFrameBuffer();

    void BindAsFrameBuffer();
    void UnBindAsFrameBuffer();
    int GetShadowMapTextureId();
    void BindAsTexture();
    void BindAsTexture(int index);

    void RenderToScreen();
};
