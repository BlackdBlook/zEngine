#include "ScreenProcessingManager.h"

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

ScreenProcessingManager::ScreenProcessingManager(GLsizei WindowX, GLsizei WindowY):
MainFrameBuffer(WindowX, WindowY),
Shader(NewSPtr<ShaderProgram>("PostProcessing", "PostProcessing-GammaCorrection"))
{
    // screen quad VAO
    unsigned int quadVBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    Shader->setUniform("screenTexture", 0);
}

void ScreenProcessingManager::PreProcessing()
{
    if(!Enabled)
    {
        return;
    }
    MainFrameBuffer.BindBuffer();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ScreenProcessingManager::PostProcessing()
{
    if(!Enabled)
    {
        return;
    }
    FrameBuffer::BindDefaultBuffer();
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    // glClear(GL_COLOR_BUFFER_BIT);
    Shader->use();
    glBindVertexArray(VAO);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, MainFrameBuffer.GetBufferTexture());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}

void ScreenProcessingManager::Enable()
{
    Enabled = true;
    LOG("ScreenProcessingManager Enable Shader:", Shader->GetName());
}

void ScreenProcessingManager::Disable()
{
    Enabled = false;
    LOG("ScreenProcessingManager Disable Shader:", Shader->GetName());
}

void ScreenProcessingManager::SetPostProcessingShader(const SPtr<ShaderProgram>& shader)
{
    Shader = shader;
}

void ScreenProcessingManager::ResetPostProcessingShader()
{
}






