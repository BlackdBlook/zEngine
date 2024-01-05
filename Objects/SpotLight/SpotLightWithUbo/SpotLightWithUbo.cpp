#include "SpotLightWithUbo.h"

#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"

void initSpotLight()
{
    SetGlobalUniformBuffer("LightData",
        "spotLight.strength",  1.0f);
    
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
        "spotLight.cutOff",   glm::cos(glm::radians(16.0f)));
    SetGlobalUniformBuffer("LightData",
        "spotLight.outerCutOff",   glm::cos(glm::radians(32.0f)));
}

void SpotLightWithUbo::InitLightBuffer()
{
    initSpotLight();
}

void SpotLightWithUbo::UpdateLightBuffer()
{
    SetGlobalUniformBuffer("LightData",
        "spotLight.position",  GetPos());

    glm::vec3 font = QuaternionUtils::forwardVectorFromQuat(GetRot());
    
    SetGlobalUniformBuffer("LightData",
        "spotLight.direction",  font);
}

void SpotLightWithUbo::DisableLight()
{
}
