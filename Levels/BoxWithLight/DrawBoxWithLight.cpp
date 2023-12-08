#include "DrawBoxWithLight.h"
#include "../../Engine/Core/Camera/Camera.h"
#include "Objects/Box/BoxWithLight.h"
#include "Objects/PointLight/PointLight.h"

void DrawBoxWithLight::Init()
{
    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(0,0,5));

    std::shared_ptr<BoxWithLight>  b = std::make_shared<BoxWithLight>(glm::vec3(0, 0, 0));
    b->SetRot(glm::vec3(45.f,45.f,0));
    std::shared_ptr<PointLight> l = std::make_shared<PointLight>(glm::vec3(2, -0.2, 0));
    b->setLight(l);
    
    objs.emplace_back(b);
    objs.emplace_back(l);
}
