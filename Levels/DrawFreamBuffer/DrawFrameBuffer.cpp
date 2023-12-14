#include "DrawFrameBuffer.h"

#include "Engine/Core/Camera/Camera.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "ToolKit/Typedef.h"

void DrawFrameBuffer::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3{0,0,5});
    
    {
        auto box = objs.emplace_back(NewSPtr<BoxV3>());

        box->SetPos(glm::vec3{0,0,-3});
        box->SetRot(glm::vec3{0,45,0});
    }

    {
        auto box = AddObject<BoxV3>();
        box->Tex = Texture2D("marble.jpg");
        box->SetScale(glm::vec3{20, 0.01, 20});
    }
    
}
