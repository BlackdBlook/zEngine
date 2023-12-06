#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
#include "Engine/Component/Component.h"
#include "Engine/Core/Camera/Camera.h"
#include "Objects/PointLightV2.h"

class PointScript : public Component
{
    static constexpr char indexChar[] = {'0','1','2','3'};
    bool EnableMoveLight;
    std::weak_ptr<ShaderProgram> TargetShader;
    std::vector<std::shared_ptr<PointLightV2>> PointLight;
public:
    PointScript(std::shared_ptr<ShaderProgram> sp, bool EnableMoveLight = true): TargetShader (sp), EnableMoveLight(EnableMoveLight)
    {
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{-3,3,0}));
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{5,3,0}));
        sp->setUniform("material.shininess", 1.f);

        auto shader = this->TargetShader.lock();
        shader->use();
        //initDirectLight();
        
        for(int i = 0;i < PointLight.size();i++)
        {
            initPointLight(i);
        }
        initSpotLight();
    }
    
    void initDirectLight();

    void initPointLight(int index);

    void updatePointLight(int index);

    void initSpotLight();

    void updateSpotLight();
    
    void Update(float DeltaTime) override;
    
    void Draw() override;
    
    ~PointScript() override = default;
};
