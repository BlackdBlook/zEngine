#pragma once
#include "Engine/Component/Component.h"

class LightComponent : public Component
{
public:

    string BufferMemberName;

    virtual void InitLightBuffer() = 0;
    
    virtual void UpdateLightBuffer() = 0;

    virtual void DisableLight() = 0;

    LightComponent();

    void Draw() override;

    void OnAttached() override;

    void OnDettached() override;
};
