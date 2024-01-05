#include "CamRot.h"

#include "Engine/Core/InputSystem/InputSystem.h"

void CamRot::Update()
{
       
    InputSystem* input = InputSystem::GetInstance();

    if(input->GetMouseButtonDown(true))
    {
        if(window == nullptr)
        {
            window = Engine::GetInstance()->GetWindow();
            glfwGetCursorPos(window,&tempX ,&tempY);
            return;
        }
        double x,y;
        glfwGetCursorPos(window,&x ,&y);
            
        glm::vec3 inputR ={ (y - tempY) * -0.2,  (x - tempX) * -0.2, 0};

        if(inputR.x != 0)
        {
            constexpr float minP = -80.0f;
            constexpr float maxP = 80.0f;
            const float tX = rot.x + inputR.x;
            if(tX < minP || tX > maxP)
            {
                inputR.x = 0;
            }
        }
            
        rot += inputR;
        rot.z = 0;

        cam->SetRot(rot);

        tempX = x;
        tempY = y;
    }else
    {
        if(window)
        {
            window = nullptr;
        }
    }
        
}
