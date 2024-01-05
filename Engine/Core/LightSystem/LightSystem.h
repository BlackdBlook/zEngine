#pragma once
#include <memory>
#include <vector>

#include "ToolKit/Typedef.h"

class LightComponent;
class SkyLight;
class SpotLightWithUbo;
class DirectLightWithUbo;
class PointLightWithUbo;

class LightSystem
{
    std::vector<WPtr<LightComponent>> Lights;
    
public:
    void RegistLightComponent(SPtr<LightComponent> Light);

    void UpdateLightBufferData();
    
    void DrawShadow();
};
