#pragma once
#include <glad/glad.h>

#include "Engine/Core/FrameBuffer/FrameBuffer.h"

class ScreenProcessingManager
{
    FrameBuffer MainFrameBuffer;

    SPtr<ShaderProgram> Shader;

    GLID VAO;

    bool Enabled = true;
    
public:
    ScreenProcessingManager(GLsizei WindowX, GLsizei WindowY);

    void PreProcessing();
    void PostProcessing();

    void Enable();
    void Disable();

    void SetPostProcessingShader(const SPtr<ShaderProgram>& shader);
    void ResetPostProcessingShader();
};
