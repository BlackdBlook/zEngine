#pragma once
#include "Engine/Core/Texture2D/Texture2D.h"
#include "Engine/Object/Object.h"
#include "Objects/PointLight.h"

class PointLightV2;

class BoxV3 : public Object
{
public:
    Texture2D Tex;
    Texture2D specular;
    Texture2D upTex;
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    Texture2D t;
    std::vector<std::shared_ptr<PointLightV2>> PointLight;

    void initDirectLight();
    
    void initPointLight(int index);
    void updatePointLight(int index);
    
    void initSpotLight();
    void updateSpotLight();
    
public:

    BoxV3();
    void Start() override;
    void Update() override;
    void Draw() override;
    ~BoxV3() override;
    void addLight(std::shared_ptr<PointLightV2> light);
};
