#include "DrawAdvanceLight.h"

#include <memory>

#include "Engine/Core/Camera/Camera.h"
#include "Objects/PointLightV2.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"

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

class LevelScript1 : public Object
{
public:
    void Update() override
    {
        const float Distance = -15.f;
        const double time = glfwGetTime() * -1;
        Camera::GetCamera()->SetPos(glm::vec3(
        sin(time) * Distance,
        0,
        cos(time) * Distance));
        
        Camera::GetCamera()->SetFont(glm::vec3(
        sin(time) * Distance,
        0,
        cos(time) * Distance));
    }
};

class LevelScript2 : public Object
{
    std::shared_ptr<PointLightV2> point_light;
public:
    LevelScript2(std::shared_ptr<PointLightV2> point_light)
        :point_light(point_light)
    {
        
    }
    void Update() override
    {
        const float Distance = 5.f;
        const double time = glfwGetTime() * -4;
        point_light->SetPos(glm::vec3(
        sin(time) * Distance,
        0,
        cos(time) * Distance));
    }
};


void DrawAdvanceLight::Init()
{
    Level::Init();
    Test2();
}

void DrawAdvanceLight::Test2()
{
    Camera::GetCamera()->Reset();

    const float Distance = 15.f;
    Camera::GetCamera()->SetPos(glm::vec3(Distance, 0, 0));
    Camera::GetCamera()->SetFont(glm::vec3(1, 0, 0));
    
    auto Light = std::make_shared<PointLightV2>(glm::vec3(Distance - 6,0,0.5));
    srand((int)glfwGetTime());

    for(int i = 0;i < 10; i++)
    {
        const float x = random_float(-5, 5);
        const float y = random_float(-3,3);
        const float z = random_float(-5, 5);
        const glm::vec3 pos {x, y, z};
        const glm::vec3 rot {
            random_float(-180.f, 180.f),
            random_float(-180.f, 180.f),
            random_float(-180.f, 180.f)
        };
        auto box = std::make_shared<BoxV3>();
        box->SetPos(pos);
        box->SetRot(rot);
        box->setLight(Light);
        objs.push_back(box);
    }
    std::cout << 1 << std::endl;

    objs.push_back(Light);
    
    
    //objs.push_back(std::make_shared<LevelScript1>());
    //objs.push_back(std::make_shared<LevelScript2>(Light));
}



void DrawAdvanceLight::Test1()
{
    Camera::GetCamera()->Reset();

    const float Distance = 3.f;
    Camera::GetCamera()->SetPos(glm::vec3(Distance, 0, 0));
    Camera::GetCamera()->SetFont(glm::vec3(1, 0, 0));
    
    auto Light = std::make_shared<PointLightV2>(glm::vec3(Distance - 2,0,0.5f));

    auto box = std::make_shared<BoxV3>();
    box->SetPos(glm::vec3{0,0,0});

    box->setLight(Light);
    
    objs.push_back(box);
    objs.push_back(Light);
    
    
    //objs.push_back(std::make_shared<LevelScript1>());
    //objs.push_back(std::make_shared<LevelScript2>(Light));
}

