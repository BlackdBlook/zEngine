#pragma once
#include "../Engine/Object/Object.h"
#include "../Header.h"
class Box :public Object
{
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    int r = 0;
    void Init();
    glm::vec3 vec;
public:
    Box(glm::vec3 pos);
    Box();
    ~Box();
    virtual void Update() override;
    virtual void Draw() override; 
};

