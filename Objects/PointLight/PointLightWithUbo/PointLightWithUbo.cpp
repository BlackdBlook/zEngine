#include "PointLightWithUbo.h"

#include <windows.h>

#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"

uint8 PointLightWithUbo::PointLightGlobalMask = 0;

static constexpr char indexChar[] = {'0','1','2','3'};
void PointLightWithUbo::initPointLight(int index)
{
    std::string s = "pointLights[";
    s += indexChar[index];
    
    SetGlobalUniformBuffer("LightData",
        (s +"].color").c_str(),  color);
    SetGlobalUniformBuffer("LightData",
        (s +"].ambient").c_str(), ambient);
    SetGlobalUniformBuffer("LightData",
        (s +"].diffuse").c_str(), diffuse);
    SetGlobalUniformBuffer("LightData",
        (s +"].specular").c_str(), specular);
    SetGlobalUniformBuffer("LightData",
        (s +"].constant").c_str(),  constant);
    SetGlobalUniformBuffer("LightData",
        (s +"].linear").c_str(),    linear);
    SetGlobalUniformBuffer("LightData",
        (s +"].quadratic").c_str(), quadratic);
}

void PointLightWithUbo::updatePointLight(int index)
{
    // if(index > 3)
    // {
    //     LOG("错误，光源类型不能超过4个");
    // }
    // auto pos = PointLight[index]->GetPos();
    //
    // std::string s = "pointLights[";
    // s += indexChar[index];
    //
    // shader->setUniform((s + "].position").c_str(), pos);
}

void initSpotLight()
{
    SetGlobalUniformBuffer("LightData",
        "spotLight.constant",  1.0f);
    // 衰减强度
    SetGlobalUniformBuffer("LightData",
        "spotLight.linear",    0.0014f);
    // 二次衰减强度
    SetGlobalUniformBuffer("LightData",
        "spotLight.quadratic", 0.000007f);
    SetGlobalUniformBuffer("LightData",
        "spotLight.color",  glm::vec3{1});
    SetGlobalUniformBuffer("LightData",
        "spotLight.ambient",  glm::vec3{0});
    SetGlobalUniformBuffer("LightData",
        "spotLight.diffuse",  glm::vec3{1}); // 将光照调暗了一些以搭配场景
    SetGlobalUniformBuffer("LightData",
        "spotLight.specular", glm::vec3{1});
    SetGlobalUniformBuffer("LightData",
        "spotLight.cutOff",   glm::cos(glm::radians(30.0f)));
    SetGlobalUniformBuffer("LightData",
        "spotLight.outerCutOff",   glm::cos(glm::radians(60.0f)));
}

void PointLightWithUbo::OnAttached()
{
    LightComponent::OnAttached();

    if(PointLightGlobalMask == 0b00001111)
    {
        LOG("Point Light Overflow");
        assert(false);
        return;
    }
    uint8 mask = 1;
    for(int i = 0;i < 8;i++)
    {
        if((PointLightGlobalMask & mask) == 0)
        {
            PointLightGlobalMask |= mask;
        }
        mask <<= 1;
    }
    PointLightIndexMask = mask;
}

void PointLightWithUbo::OnDettached()
{
    LightComponent::OnDettached();

    PointLightGlobalMask ^= PointLightIndexMask;
}

void PointLightWithUbo::InitLightBuffer()
{
    switch(PointLightIndexMask)
    {
    case 1 << 0:
        initPointLight(0);
        break;
    case 1 << 1: 
        initPointLight(1);
        break;
    case 1 << 2:
        initPointLight(2);
        break;
    case 1 << 3:
        initPointLight(3);
        break;
    default:
        LOG("Error Point Light Index");
    }
    
}

void PointLightWithUbo::UpdateLightBuffer()
{
}
