#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
class PointLightV2 : public Object
{
    GLID vao;
    GLID vbo;
    std::shared_ptr<ShaderProgram> shader;

public:
    void Init();
    virtual void Update() override;
    virtual void Draw() override;
    PointLightV2(glm::vec3 pos);
    ~PointLightV2() override;
};
