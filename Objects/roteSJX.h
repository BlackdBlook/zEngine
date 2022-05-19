#pragma once
#include "../Engine/Object/Object.h"
#include "../Header.h"

class roteSJX:public Object
{
    GLID vao;
    GLID vbo;
    std::shared_ptr<class ShaderProgram> program;
    bool b;
public:
    roteSJX(bool b);
    virtual void Draw()override;
    virtual void Update()override;
    virtual ~roteSJX();

};

