#include "PointLightComponent.h"

#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"

struct LightGlobalUniform
{
    
};

void PointLightComponent::OnAttached()
{
    Component::OnAttached();
}

void PointLightComponent::OnDettached()
{
    Component::OnDettached();
}

void PointLightComponent::Draw()
{
    Component::Draw();
}

void PointLightComponent::Update(float DeltaTime)
{
    Component::Update(DeltaTime);

    //LightGlobalUniform light;
    
    // SetGlobalUniformBuffer("", light);
}

void PointLightComponent::Destory()
{
    Component::Destory();
}

PointLightComponent::~PointLightComponent()
{
}
