#pragma once
#include "ObjectHeader.h"
class PointLight : public Object
{
    GLID vao;
    GLID vbo;
    std::shared_ptr<ShaderProgram> shader;

public:
    void Init();
    virtual void Update() override;
    virtual void Draw() override;
    PointLight(glm::vec3 pos);
    ~PointLight();
};

