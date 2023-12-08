#pragma once
#include "Engine/Object/Object.h"
#include "ToolKit/Typedef.h"

class PointLight;
class ShaderProgram;

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
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override; 

    void setLight(std::shared_ptr<PointLight> light);
};

