#include "DrawFrameBuffer.h"

#include "Engine/zEngine.h"
#include "Engine/Component/Component.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/ScreenProcessingManager/ScreenProcessingManager.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "ToolKit/Typedef.h"

class SwitchPostProcessing : public Component
{
public:
    void Update(float DeltaTime) override;

    bool KeyDown = false;

    bool PostProcessingEnable = true;
};

void SwitchPostProcessing::Update(float DeltaTime)
{
    Component::Update(DeltaTime);


    if (KeyDown == false && 
        glfwGetKey(Engine::GetInstance()->GetWindow(),GLFW_KEY_E) == GLFW_PRESS)
    {
        if(PostProcessingEnable)
        {
            PostProcessingEnable = false;
            KeyDown = true;
            Engine::GetInstance()->GetScreenProcessingManagerPtr()->Disable();
        }else
        {
            PostProcessingEnable = true;
            KeyDown = true;
            Engine::GetInstance()->GetScreenProcessingManagerPtr()->Enable();
        }
    }else if(KeyDown == true &&
        glfwGetKey(Engine::GetInstance()->GetWindow(),GLFW_KEY_E) != GLFW_PRESS)
    {
        KeyDown = false;
    }

    
}


void DrawFrameBuffer::Init()
{
    Level::Init();

    auto cam = Camera::GetCamera();
    
    cam->Reset();
    
    {
        auto box = AddObject<BoxV3>();
        box->shader = NewSPtr<ShaderProgram>("TestShader");
        box->SetPos(glm::vec3{0,0,-5});
        box->SetRot(glm::vec3{0,45,0});
    }

    {
        auto box = AddObject<BoxV3>();
        box->Tex = Texture2D("marble.jpg");
        box->SetScale(glm::vec3{20, 0.01, 20});
    }

    {
        auto script = NewObject();
        script->Attach(NewSPtr<SwitchPostProcessing>());
    }
}
