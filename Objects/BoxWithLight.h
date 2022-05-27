#pragma once
#include "../Engine/Object/Object.h"
#include "../Header.h"
class BoxWithLight :public Object
{
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    int r = 0;
    void Init();
    glm::vec3 vec;
public:
    BoxWithLight(glm::vec3 pos);
    BoxWithLight();
    ~BoxWithLight();
    virtual void Update() override;
    virtual void Draw() override; 
};

