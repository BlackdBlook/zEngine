#include "TurnModelScript.h"

#include "Header.h"
#include "Engine/zEngine.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/InputSystem/InputSystem.h"

void TurnModelScript::OnAttached()
{
    input = InputSystem::GetInstance();
    //window = Engine::GetInstance()->GetWindow();
}

void TurnModelScript::Update(float DeltaTime)
{
    if(input)
    {
        if(input->GetMouseButtonDown(true))
        {
            if(window == nullptr)
            {
                window = Engine::GetInstance()->GetWindow();
                glfwGetCursorPos(window,&tempPoint.x ,&tempPoint.y);
                return;
            }
            POINT x;
            glfwGetCursorPos(window,&x.x ,&x.y);
            const auto p = Parent.lock();
            
            glm::vec3 inputR =
                {0, x.x - tempPoint.x, 0};

            p->AddRot(inputR * 0.5f);

            tempPoint = x;
        }else
        {
            if(window)
            {
                window = nullptr;
            }
        }
    }
}

void TurnModelScript::Draw()
{
    Component::Draw();
}
