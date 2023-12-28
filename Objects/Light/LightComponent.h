#pragma once
#include "Engine/Component/Component.h"

class LightComponent : public Component
{
public:

    string BufferMemberName;

    virtual void InitLightBuffer() = 0;
    
    virtual void UpdateLightBuffer() = 0;
};
