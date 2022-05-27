#include "BoxWithLight.h"
#include "../../Objects/Box.h"
#include "../../Objects/PointLight.h"
#include "../../Engine/Core/Camera/Camera.h"
void DrawBoxWithLight::Init()
{
    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(10,0,0));
    Camera::GetCamera()->SetFont(glm::vec3(1,0,0));

    std::shared_ptr<Box> b = std::make_shared<Box>(glm::vec3(3, 2, 0));
    b->SetRot(glm::vec3(45.f,45.f,0));
    objs.emplace_back(b);
    objs.emplace_back(new PointLight(glm::vec3(-5, -2, 0)));
}
