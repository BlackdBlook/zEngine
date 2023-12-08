#pragma once
#include "Engine/Core/Texture2D/Texture2D.h"
#include "Engine/Object/Object.h"

class PointLightV2;

class BoxV3 : public Object
{
public:
    Texture2D Tex;
    Texture2D specular;
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;

    std::vector<std::shared_ptr<PointLightV2>> PointLight;

    void initDirectLight();
    
    void initPointLight(int index);
    void updatePointLight(int index);
    
    void initSpotLight();
    void updateSpotLight();
    
public:

    BoxV3();
    BoxV3(const char* diff, const char* spec);
    void Start() override;
    void Update(float DeltaTime) override;
    void Draw() override;
    ~BoxV3() override;
    void addLight(std::shared_ptr<PointLightV2> light);
};
