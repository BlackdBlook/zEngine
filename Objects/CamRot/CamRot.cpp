﻿#include "CamRot.h"

#include "Engine/Core/InputSystem/InputSystem.h"

void CamRot::Update(float DeltaTime)
{
    constexpr float MOVE_SPEED = 5;
    glm::vec3 pos = cam->GetPos();
    const float MoveSpeed = MOVE_SPEED * DeltaTime;
    bool flag = false;
    auto r = cam->GetRight();
    r.y = 0;
    r = glm::normalize(r);
    auto u = glm::vec3{0, 1, 0};
    u = glm::normalize(u);
    auto f = glm::cross(r,u);
    f = glm::normalize(f);
        
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        pos+= MoveSpeed * f;
        flag = true;
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        pos+= -MoveSpeed * f;
        flag = true;
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        pos += MoveSpeed * r;
        flag = true;
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        pos += -MoveSpeed * r;
        flag = true;
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        pos+= MoveSpeed * u;
        flag = true;
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        pos+= -MoveSpeed * u;
        flag = true;
    }
    if(flag)
    {
        cam->SetPos(pos);
    }
       
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
