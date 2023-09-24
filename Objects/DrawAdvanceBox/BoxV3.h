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
    std::shared_ptr<PointLightV2> Light;
    
public:

    BoxV3();
    void Start() override;
    void Update() override;
    void Draw() override;
    ~BoxV3() override;
    void setLight(std::shared_ptr<PointLightV2> light);
};
