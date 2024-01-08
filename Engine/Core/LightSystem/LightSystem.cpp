#include "LightSystem.h"
#include "Engine/Core/ShaderProgram.h"
#include "Engine/Core/DrawCommand/RenderCommandQueue.h"
#include "Engine/Core/TextureSceneDepth/SceneDepthFrameBuffer.h"

LightSystem::LightSystem()
{
    SceneDepthFrameBufferPtr = NewSPtr<SceneDepthFrameBuffer>();
}

void LightSystem::BindShadowMapTexture(ShaderProgram* shader)
{
    assert(shader);
    shader->setUniform("dirLightShadowMap",
        SceneDepthFrameBufferPtr->GetShadowMapTextureId());
}

void LightSystem::RegistLightComponent(SPtr<LightComponent> Light)
{
    
}

void LightSystem::UpdateLightBufferData()
{    

    

}

void LightSystem::DrawShadow()
{
    SceneDepthFrameBufferPtr->BindAsFrameBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);
    RenderCommandQueue::GetInstance().RenderShadow();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}

void LightSystem::ActiveSceneDepthFrameBufferTexture()
{
    SceneDepthFrameBufferPtr->BindAsTexture();
    
}

void LightSystem::RenderSceenDepthFrameBufferToScreen()
{
    SceneDepthFrameBufferPtr->RenderToScreen();
}

LightSystem* LightSystem::GetInstance()
{
    static LightSystem* ans = new LightSystem();
    return ans;
}
