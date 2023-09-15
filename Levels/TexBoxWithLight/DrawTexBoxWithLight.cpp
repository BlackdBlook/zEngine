#include "DrawTexBoxWithLight.h"
#include "../../Objects/Box.h"
#include "../../Objects/PointLight.h"
#include "../../Engine/Core/Camera/Camera.h"
#include "../../Objects/TexBoxWithLight.h"
void DrawTexBoxWithLight::Init()
{
    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(5,0,0));
    Camera::GetCamera()->SetFont(glm::vec3(1,0,0));

    std::shared_ptr<TexBoxWithLight>  b = std::make_shared<TexBoxWithLight>(glm::vec3(0, 0, 0));
    b->SetRot(glm::vec3(45.f,45.f,0));
    std::shared_ptr<PointLight> l = std::make_shared<PointLight>(glm::vec3(2, -0.2, 0));
    b->setLight(l);
    objs.emplace_back(b);
    objs.emplace_back(l);
}
