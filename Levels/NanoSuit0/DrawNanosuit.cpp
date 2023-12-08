#include "DrawNanosuit.h"

#include <memory>

#include "Engine/zEngine.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Objects/PointLight/PointLightV3.h"
#include "Objects/TurnModelScript/TurnModelScript.h"

DrawNanosuit::~DrawNanosuit()
{
}






void DrawNanosuit::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(0,0,20));
    
    std::string name = std::string{"nanosuit.obj"};
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("NanoSuit0");

    auto m = NewObject();
    m->Attach(std::make_shared<Model>(std::move(name), sp));
    m->Attach(std::make_shared<TurnModelScript>());
    m->Attach(std::make_shared<PointScript>(sp));
    m->SetPos(glm::vec3{0,-10,0});
    m->SetRot(glm::vec3{0,0,0});
    
    
}
