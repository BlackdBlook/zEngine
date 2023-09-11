#pragma once
#include "../Engine/Object/Object.h"
#include "../Header.h"
#include "PointLight.h"
class TexBoxWithLight :public Object
{
    GLID vao,vbo;
    Texture2D Tex;
    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<PointLight> Light;
    int r = 0;
    void Init();
    glm::vec3 vec;
public:
    TexBoxWithLight(glm::vec3 pos);
    TexBoxWithLight();
    virtual ~TexBoxWithLight() override;
    virtual void Update() override;
    virtual void Draw() override; 

    void setLight(std::shared_ptr<PointLight> light);
};

