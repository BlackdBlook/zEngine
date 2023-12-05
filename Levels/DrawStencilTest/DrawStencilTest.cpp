#include "DrawStencilTest.h"

#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Object/Object.h"
#include "Objects/MeshOutline/MeshOutline.h"
#include "Objects/PointLight/PointLightV3.h"
#include "Objects/TurnModelScript/TurnModelScript.h"

void DrawStencilTest::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3{0,0,20});

    std::string name = std::string{"nanosuit.obj"};
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("NanoSuit0");

    auto m = NewObject();
    m->Attach(std::make_shared<MeshOutline>(name.c_str(), sp));
    m->Attach(std::make_shared<TurnModelScript>());
    m->SetPos(glm::vec3{0,-10,0});
    m->SetRot(glm::vec3{0,0,0});


    objs.push_back(std::make_shared<PointScript>(sp));
}
