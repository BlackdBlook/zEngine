﻿#pragma once
#include "Engine/Object/Object.h"
#include "ToolKit/Typedef.h"

class ShaderProgram;

class SkyBox : public Object
{
    SPtr<ShaderProgram> shader;
    unsigned int cubemapTexture;
    unsigned int skyboxVAO, skyboxVBO;

public:
    void Start() override;
    void Update(float DeltaTime) override;
    void Draw() override;
    ~SkyBox() override;
};
