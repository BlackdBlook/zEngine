#pragma once
#include <memory>
#include <vector>

#include "ToolKit/Typedef.h"

class ShaderProgram;
class SceneDepthFrameBuffer;
class LightComponent;
class SkyLight;
class SpotLightWithUbo;
class DirectLightWithUbo;
class PointLightWithUbo;

class LightSystem
{
    std::vector<WPtr<LightComponent>> Lights;

    SPtr<SceneDepthFrameBuffer> SceneDepthFrameBufferPtr;

    LightSystem();
public:
    void BindShadowMapTexture(ShaderProgram* shader);
    
    void RegistLightComponent(SPtr<LightComponent> Light);

    void UpdateLightBufferData();
    
    void DrawShadow();

    void ActiveSceneDepthFrameBufferTexture();

    void RenderSceenDepthFrameBufferToScreen();

    static LightSystem* GetInstance();
};
