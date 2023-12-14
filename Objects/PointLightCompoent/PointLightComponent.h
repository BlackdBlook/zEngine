#pragma once
#include "Engine/Component/Component.h"

class PointLightComponent : public Component
{
public:
    void OnAttached() override;
    void OnDettached() override;
    void Draw() override;
    void Update(float DeltaTime) override;
    void Destory() override;
    ~PointLightComponent() override;
};
