#pragma once

#include "Header.h"
#include "Engine/Component/Component.h"


class PointLightV2;

class PointScript : public Component
{
    static constexpr char indexChar[] = {'0','1','2','3'};
    bool EnableMoveLight;
    std::weak_ptr<ShaderProgram> TargetShader;
    std::vector<std::shared_ptr<PointLightV2>> PointLight;
public:
    PointScript(std::shared_ptr<ShaderProgram> sp, bool EnableMoveLight = true);
    
    void initDirectLight();

    void initPointLight(int index);

    void updatePointLight(int index);

    void initSpotLight();

    void updateSpotLight();
    
    void Update(float DeltaTime) override;
    
    void Draw() override;
    
    ~PointScript() override = default;
};
