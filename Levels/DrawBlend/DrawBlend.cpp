#include "DrawBlend.h"

#include "Engine/zEngine.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/InputSystem/InputSystem.h"
#include "Engine/Object/Object.h"
#include "MeshData/Box/Mesh_Box.h"
#include "Objects/CamRot/CamRot.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "Objects/PlaneWithLight/PlaneWithLight.h"
#include "Objects/PointLight/PointLightV3.h"
#include "Objects/TurnModelScript/TurnModelScript.h"
#include "ToolKit/Typedef.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"

void DrawBlend::Init()
{
    Level::Init();
    auto cam = Camera::GetCamera();
    
    cam->Reset([cam](float DeltaTime)
    {
        static CamRot rot;
        rot.Update(DeltaTime);
        
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
