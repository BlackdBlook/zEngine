#include "DrawBlend.h"

#include "Engine/zEngine.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/InputSystem/InputSystem.h"
#include "Engine/Object/Object.h"
#include "MeshData/Box/Mesh_Box.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "Objects/PlaneWithLight/PlaneWithLight.h"
#include "Objects/PointLight/PointLightV3.h"
#include "Objects/TurnModelScript/TurnModelScript.h"
#include "ToolKit/Typedef.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"

  
class CamRot
{
    glm::vec3 rot {0};
    Camera* cam = Camera::GetCamera();
    GLFWwindow* window = nullptr;
    double tempX, tempY;
public:
    void Update()
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
};


void DrawBlend::Init()
{
    Level::Init();
    auto cam = Camera::GetCamera();
    
    cam->Reset([cam](float DeltaTime)
    {
        constexpr float MOVE_SPEED = 20;
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

        static CamRot rot;
        rot.Update();
        
    });
    
    cam->SetPos(glm::vec3{0,0, 20});
    


    {
        auto plan = std::static_pointer_cast<BoxV3>(
        objs.emplace_back(NewSPtr<BoxV3>("marble.jpg", "marble.jpg")));
    
        plan->SetPos(glm::vec3{0,0,0});
        plan->SetScale(glm::vec3{100.f,0.01f,100.f});
    }

    {
        std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("NanoSuit0");
            
        std::string name = std::string{"nanosuit.obj"};
        auto m = NewObject();
        m->Attach(std::make_shared<Model>(std::move(name), sp));
    
        m->Attach(std::make_shared<PointScript>(sp, false));
        m->SetPos(glm::vec3{0,-10,-10});
        m->SetRot(glm::vec3{0,0,0});
    }


    {
        auto plan = std::static_pointer_cast<BoxV3>(
        objs.emplace_back(NewSPtr<BoxV3>(
            "blending_transparent_window.png", "blending_transparent_window.png")));
        plan->shader = NewSPtr<ShaderProgram>("DrawBlend");
        plan->shader->BlendType = BlendType::Translucent;
        plan->SetPos(glm::vec3{0,10,0});
        plan->SetRot(glm::vec3{0,0,0});
        plan->SetScale(glm::vec3{8,8,0.001});
    }

    {
        auto plan = std::static_pointer_cast<BoxV3>(
        objs.emplace_back(NewSPtr<BoxV3>(
            "blending_transparent_window.png", "blending_transparent_window.png")));
        plan->shader = NewSPtr<ShaderProgram>("DrawBlend");
        plan->shader->BlendType = BlendType::Translucent;
        plan->SetPos(glm::vec3{0,10,10});
        plan->SetRot(glm::vec3{0,0,0});
        plan->SetScale(glm::vec3{8,8,0.001});
    }

    {
        auto plan = std::static_pointer_cast<BoxV3>(
        objs.emplace_back(NewSPtr<BoxV3>("grass.png","grass.png")));
        plan->shader = NewSPtr<ShaderProgram>("DrawBlend");
        //plan->SetPos(glm::vec3{5,10,5});
        plan->SetPos(glm::vec3{-2,10,5});
        plan->SetRot(glm::vec3{0,0,0});
        plan->SetScale(glm::vec3{1,1,1});
    }
    
    
}
