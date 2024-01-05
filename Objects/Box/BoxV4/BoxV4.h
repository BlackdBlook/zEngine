#pragma once
#include "Engine/Component/Component.h"

class BoxV4 : public Component
{
public:
    GLID vao, vbo;
    Texture2D Tex;
    Texture2D Tex2;
    SPtr<ShaderProgram> shader;

    BoxV4();
    
    void OnAttached() override;
    void OnDettached() override;
    void Draw() override;
    void Update(float DeltaTime) override;
    void Destory() override;
    ~BoxV4() override;
};
