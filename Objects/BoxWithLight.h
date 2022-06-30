#pragma once
#include "../Engine/Object/Object.h"
#include "../Header.h"
#include "PointLight.h"
class BoxWithLight :public Object
{
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<PointLight> Light;
    int r = 0;
    void Init();
    glm::vec3 vec;
public:
    BoxWithLight(glm::vec3 pos);
    BoxWithLight();
    ~BoxWithLight();
    virtual void Update() override;
    virtual void Draw() override; 

    void setLight(std::shared_ptr<PointLight> light);
};

