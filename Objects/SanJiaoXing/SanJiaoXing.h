#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
class SanJiaoXing :public Object
{
    GLID vao;
    class ShaderProgram* program;
public:
    SanJiaoXing();
    virtual void Draw()override;
    virtual void Update(float DeltaTime)override;
};

