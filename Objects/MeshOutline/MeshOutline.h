#pragma once
#include "MeshOutline.h"
#include "Engine/Component/Component.h"
#include "Engine/Component/Model/Model.h"

class MeshOutline : public Model
{
    std::shared_ptr<ShaderProgram> sp;
public:

    MeshOutline(const char* modelName, std::shared_ptr<ShaderProgram> shader);
    
    float OutlineSize = 0.05f;

    
    void Draw() override;
};
