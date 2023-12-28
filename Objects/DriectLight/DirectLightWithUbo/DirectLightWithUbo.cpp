#include "DirectLightWithUbo.h"

#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"

void DirectLightWithUbo::InitLightBuffer()
{
    SetGlobalUniformBuffer("LightData", "dirLight.direction", direction);
    SetGlobalUniformBuffer("LightData", "dirLight.color", color);
    SetGlobalUniformBuffer("LightData", "dirLight.ambient", ambient);
    SetGlobalUniformBuffer("LightData", "dirLight.diffuse", diffuse);
    SetGlobalUniformBuffer("LightData", "dirLight.specular", specular);
}

void DirectLightWithUbo::UpdateLightBuffer()
{
    if(DirtyMask == 0)
    {
        return;
    }
    if(DirtyMask & 1 << 0)
    {
        SetGlobalUniformBuffer("LightData", "dirLight.direction", direction);
    }
    if(DirtyMask & 1 << 1)
    {
        SetGlobalUniformBuffer("LightData", "dirLight.color", color);
    }
    if(DirtyMask & 1 << 2)
    {
        SetGlobalUniformBuffer("LightData", "dirLight.ambient", ambient);
    }
    if(DirtyMask & 1 << 3)
    {
        SetGlobalUniformBuffer("LightData", "dirLight.diffuse", diffuse);
    }
    if(DirtyMask & 1 << 4)
    {
        SetGlobalUniformBuffer("LightData", "dirLight.specular", specular);
    }
    DirtyMask = 0;
}
