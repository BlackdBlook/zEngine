#include "DrawShadow.h"

#include <glm/vec3.hpp>

#include "Engine/zEngine.h"
#include "Engine/Core/Camera/Camera.h"
#include "Objects/Box/BoxV4/BoxV4.h"
#include "Objects/CamRot/CamRot.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "Objects/DriectLight/DirectLightWithUbo/DirectLightWithUbo.h"
#include "Objects/PointLight/PointLightWithUbo/PointLightWithUbo.h"
#include "Objects/SkyBox/SkyBox.h"
#include "Objects/SpotLight/SpotLightWithUbo/SpotLightWithUbo.h"

namespace
{
    float random_float(float min, float max) {
        // 生成0到1之间的随机浮点数
        const float random = ((float) rand()) / (float) RAND_MAX;

        // 调整随机数的范围到[min, max]
        const float range = max - min;  
        return (random*range) + min;
    }
}

class SpotLightControlScript : public Component
{
    void Update(float DeltaTime) override;
};

void SpotLightControlScript::Update(float DeltaTime)
{
    Component::Update(DeltaTime);

    auto p = Parent.lock();
    p->SetPos(Camera::GetCamera()->GetPos());
    p->SetRot(Camera::GetCamera()->GetRot());
}

void DrawShadow::Init()
{
    Level::Init();
    auto cam = Camera::GetCamera();
    
    cam->Reset([cam](float DeltaTime)
    {
        static CamRot rot;
        rot.Update(DeltaTime);
    });
    Camera::GetCamera()->SetPos(glm::vec3{0,0,5});

    
    // {
    //     auto Light = NewObject();
    //     auto DirLight = NewSPtr<DirectLightWithUbo>();
    //     Light->Attach(DirLight);
    // }

    {
        
        for(int i = 0;i < 4;i++)
        {
            auto l = NewObject();
            auto p = NewSPtr<PointLightWithUbo>();
            l->Attach(p);
            const float range = 5; 
            float x1 = random_float(-range,range);
            float x2 = random_float(-range,range);
            float x3 = random_float(-range,range);
                
            l->SetPos(glm::vec3{x1,x2,x3});
            l->SetScale(glm::vec3{0.1f,0.1f,0.1f});
        }
        
    }

    {
        auto Light = NewObject();
        auto Spot = NewSPtr<SpotLightWithUbo>();
        Light->Attach(Spot);
        Light->Attach(NewSPtr<SpotLightControlScript>());
    }

    {
        auto obj = NewObject();
        auto box = NewSPtr<BoxV4>();
        obj->Attach(box);
        obj->SetPos(glm::vec3{0,0,-5});
    }

    {
        auto obj = NewObject();
        auto box = NewSPtr<BoxV4>();
        box->Tex = {"marble.jpg"};
        box->Tex2 = {"marble.jpg"};
        obj->Attach(box);
        obj->SetPos(glm::vec3{0,-2,0});
        obj->SetScale(glm::vec3{30.f,0.1f,30.f});
    }

    {
        // objs.emplace_back(NewSPtr<SkyBox>());
    }

}
