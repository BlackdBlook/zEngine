#include "DrawAdvanceLight.h"

#include <memory>

#include "Engine/Core/Camera/Camera.h"
#include "Objects/DrawAdvanceBox/BoxV3.h"
#include "Objects/PointLight/PointLightV2.h"

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
    void Update(float DeltaTime) override
    {
        const float Distance = -15.f;
        const double time = glfwGetTime() * -1;
        Camera::GetCamera()->SetPos(glm::vec3(
        sin(time) * Distance,
        0,
        cos(time) * Distance));
        
        Camera::GetCamera()->SetRot(glm::vec3(
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
    void Update(float DeltaTime) override
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
    Camera::GetCamera()->SetPos(glm::vec3(0, 0, Distance));
    
    srand((int)glfwGetTime());
    
    std::vector<std::shared_ptr<PointLightV2>> points;

    for(int i = 0;i < 4; i++)
    {
        const float x = random_float(-5, 5);
        const float y = random_float(-3,3);
        const float z = random_float(-5, 5);
        points.emplace_back(std::make_shared<PointLightV2>(glm::vec3( x, y, z)));
        objs.push_back(points[i]);
    }

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
        for(auto l : points)
        {
            box->addLight(l);
        }
        objs.push_back(box);
    }
    
    //objs.push_back(std::make_shared<LevelScript1>());
    //objs.push_back(std::make_shared<LevelScript2>(Light));
}



void DrawAdvanceLight::Test1()
{
    Camera::GetCamera()->Reset();

    const float Distance = 3.f;
    Camera::GetCamera()->SetPos(glm::vec3(Distance, 0, 0));
    
    auto Light = std::make_shared<PointLightV2>(glm::vec3(Distance - 2,0,0.5f));

    auto box = std::make_shared<BoxV3>();
    box->SetPos(glm::vec3{0,0,0});

    box->addLight(Light);
    
    objs.push_back(box);
    objs.push_back(Light);
    
    
    //objs.push_back(std::make_shared<LevelScript1>());
    //objs.push_back(std::make_shared<LevelScript2>(Light));
}

