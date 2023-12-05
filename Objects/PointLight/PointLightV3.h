#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
#include "Engine/Core/Camera/Camera.h"
#include "Objects/PointLightV2.h"

class PointScript : public Object
{
    static constexpr char indexChar[] = {'0','1','2','3'};
    std::shared_ptr<ShaderProgram> shader;
    std::vector<std::shared_ptr<PointLightV2>> PointLight;
public:
    PointScript(std::shared_ptr<ShaderProgram> sp): shader (sp)
    {
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{-3,3,0}));
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{5,3,0}));
        shader->setUniform("material.shininess", 1.f);
    }
    void Start() override;
    
    void initDirectLight();

    void initPointLight(int index);

    void updatePointLight(int index);

    void initSpotLight();

    void updateSpotLight();
    
    void Update(float DeltaTime) override;
    
    void Draw() override;
    
    ~PointScript() override = default;
};
