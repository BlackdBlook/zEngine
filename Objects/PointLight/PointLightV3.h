#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"

// 使用全局Uniform的点光
class PointLightV3 : public Object
{
    GLID vao;
    GLID vbo;
    std::shared_ptr<ShaderProgram> shader;

public:
    void Init();
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;
    PointLightV3(glm::vec3 pos);
    ~PointLightV3() override;
};
