#include "LightComponent.h"

LightComponent::LightComponent()
{
    
}

void LightComponent::Draw()
{
    Component::Draw();

    UpdateLightBuffer();
}

void LightComponent::OnAttached()
{
    Component::OnAttached();
    
    InitLightBuffer();
}

void LightComponent::OnDettached()
{
    Component::OnDettached();
    
    DisableLight();
}
