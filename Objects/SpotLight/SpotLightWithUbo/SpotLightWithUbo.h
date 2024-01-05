#pragma once
#include "Objects/Light/LightComponent.h"

class SpotLightWithUbo : public LightComponent
{
public:
    void InitLightBuffer() override;
    void UpdateLightBuffer() override;
    void DisableLight() override;
};
