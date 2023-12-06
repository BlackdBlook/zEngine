#include "DrawDepthTestBuffer.h"

#include "Engine/zEngine.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/InputSystem/InputSystem.h"
#include "Objects/PointLightV2.h"
#include "Objects/TurnModelScript/TurnModelScript.h"


void DrawDepthTestBuffer::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(0,0,15));
    
    std::string name = std::string{"nanosuit.obj"};
    {
        std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>(
            "NanoSuit0", "DepthTest");

        auto m = NewObject();
        m->Attach(std::make_shared<Model>(name, sp));
        m->Attach(std::make_shared<TurnModelScript>());
        m->SetPos(glm::vec3{5,-10,-0});
        m->SetRot(glm::vec3{0,0,0});
    }

    {
        std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>(
            "NanoSuit0", "DepthTest");

        auto m = NewObject();
        m->Attach(std::make_shared<Model>(std::move(name), sp));
        m->Attach(std::make_shared<TurnModelScript>());
        m->SetPos(glm::vec3{-5,-10,-30});
        m->SetRot(glm::vec3{0,0,0});
    }
    
}
