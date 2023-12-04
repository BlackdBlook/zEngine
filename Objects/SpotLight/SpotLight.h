#pragma once
#include "Engine/Object/Object.h"
#include "Header.h"
class SpotLight : public Object
{
    GLID vao;
    GLID vbo;
    std::shared_ptr<ShaderProgram> shader;
public:
    SpotLight(glm::vec3 pos);
    ~SpotLight() override;
    void Init();
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

};
