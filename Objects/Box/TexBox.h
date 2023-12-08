#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
class TexBox :public Object
{
    GLID vao,vbo;
    std::shared_ptr<ShaderProgram> shader;
    Texture2D t;
    int r = 0;
    void Init();
    glm::vec3 vec;
public:
    TexBox(glm::vec3 pos);
    TexBox();
    ~TexBox();
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override; 
};

