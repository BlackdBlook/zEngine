#pragma once
#include "../Header.h"
#include "../Engine/Object/Object.h"

class PointLight;
class ShaderProgram;

class BoxWithMaterial : public Object
{
    Texture2D Tex;
    Texture2D specular;
    Texture2D upTex;
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    Texture2D t;
    std::shared_ptr<PointLight> Light;
    
public:

    BoxWithMaterial();
    void Start() override;
    void Update() override;
    void Draw() override;
    ~BoxWithMaterial() override;
    void setLight(std::shared_ptr<PointLight> light);
};
