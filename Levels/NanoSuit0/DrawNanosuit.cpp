﻿#include "DrawNanosuit.h"

#include <memory>

#include "Engine/zEngine.h"
#include "GLFW/glfw3.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/InputSystem/InputSystem.h"
#include "Objects/PointLightV2.h"

DrawNanosuit::~DrawNanosuit()
{
}

class PointScript : public Object
{
    static constexpr char indexChar[] = {'0','1','2','3'};
    std::shared_ptr<ShaderProgram> shader;
    std::vector<std::shared_ptr<PointLightV2>> PointLight;
public:
    PointScript(std::shared_ptr<ShaderProgram> sp): shader (sp)
    {
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{-3,3,0}));
        PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{5,3,0}));
        shader->setUniform("material.shininess", 1.f);
    }
    void Start() override
    {
        shader->use();
        initDirectLight();
        
        for(int i = 0;i < PointLight.size();i++)
        {
            initPointLight(i);
        }
        initSpotLight();
    }
    
    void initDirectLight()
    {
        shader->setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader->setUniform("dirLight.ambient", glm::vec3{0.4f});
        shader->setUniform("dirLight.diffuse", glm::vec3{0.4f});
        shader->setUniform("dirLight.specular", glm::vec3{0.5f});
    }

    void initPointLight(int index)
    {
        shader->setUniform("PointLightCount", index + 1);
        if(index > 4)
        {
            LOG("错误，光源类型不能超过4个");
        }
        std::string s = "pointLights[";
        s += indexChar[index];
        
        shader->setUniform((s +"].color").c_str(),  glm::vec3{0});
        shader->setUniform((s +"].ambient").c_str(),    glm::vec3{0.4f});
        shader->setUniform((s +"].diffuse").c_str(),     glm::vec3{0.4f});
        shader->setUniform((s +"].specular").c_str(),    glm::vec3{0.5f});
        shader->setUniform((s +"].constant").c_str(),  1.0f);
        shader->setUniform((s +"].linear").c_str(),    0.09f);
        shader->setUniform((s +"].quadratic").c_str(), 0.032f);

        //shader->setUniform("light.color",  1.f, 1.f, 1.f);
    }

    void updatePointLight(int index)
    {
        if(index > 3)
        {
            LOG("错误，光源类型不能超过4个");
        }
        auto pos = PointLight[index]->GetPos();
        
        std::string s = "pointLights[";
        s += indexChar[index];

        shader->setUniform((s + "].position").c_str(), pos);
    }

    void initSpotLight()
    {
        shader->setUniform("spotLight.constant",  1.0f);
        // 衰减强度
        shader->setUniform("spotLight.linear",    0.0014f);
        // 二次衰减强度
        shader->setUniform("spotLight.quadratic", 0.000007f);
        shader->setUniform("spotLight.ambient",  glm::vec3{0.4f});
        shader->setUniform("spotLight.diffuse",  glm::vec3{1}); // 将光照调暗了一些以搭配场景
        shader->setUniform("spotLight.specular", glm::vec3{0.5f});
        shader->setUniform("spotLight.cutOff",   glm::cos(glm::radians(10.0f)));
        shader->setUniform("spotLight.outerCutOff",   glm::cos(glm::radians(15.0f)));
    }

    void updateSpotLight()
    {
        shader->setUniform("spotLight.position", Camera::GetCamera()->GetPos());
        shader->setUniform("spotLight.direction", -Camera::GetCamera()->GetFont());
    }

    
    void Update(float DeltaTime) override
    {
        PointLight[0]->Update(DeltaTime);
        PointLight[1]->Update(DeltaTime);
        Camera::GetCamera()->Update(DeltaTime);

    }
    void Draw() override
    {
        updateSpotLight();
        for(int i = 0;i < PointLight.size();i++)
        {
            updatePointLight(i);
            PointLight[0]->Draw();
            PointLight[1]->Draw();
        }
        
    }
    ~PointScript() override = default;
};


class TurnModelScript : public Object
{
    struct POINT
    {
        double x;
        double y;
    };

public:
    TurnModelScript(std::shared_ptr<Object> Target) : Target(Target)
    {
        
    }
    void Start() override
    {
        input = InputSystem::GetInstance();
        //window = Engine::GetInstance()->GetWindow();
    }
    void Update(float DeltaTime) override
    {
        if(input)
        {
            if(input->GetMouseButtonDown(true))
            {
                if(window == nullptr)
                {
                    window = Engine::GetInstance()->GetWindow();
                    glfwGetCursorPos(window,&tempPoint.x ,&tempPoint.y);
                    return;
                }
                POINT x;
                glfwGetCursorPos(window,&x.x ,&x.y);

                Target->SetRot(Target->GetRot() + glm::vec3{0, x.x - tempPoint.x, 0});
                
                tempPoint = x;
            }else
            {
                if(window)
                {
                    window = nullptr;
                }
            }
        }
    }
    void Draw() override
    {
        
    }
    ~TurnModelScript() override = default;

private:
    POINT tempPoint = { 10,10 };
    InputSystem* input = nullptr;
    GLFWwindow* window = nullptr;
    std::shared_ptr<Object> Target;
};

void DrawNanosuit::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(0,0,20));
    
    std::string name = std::string{"nanosuit.obj"};
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("NanoSuit0");

    auto m = std::make_shared<Model>(std::move(name), sp);
    objs.push_back(m);
    m->SetPos(glm::vec3{0,-10,0});
    m->SetRot(glm::vec3{0,0,0});

    objs.push_back(std::make_shared<PointScript>(sp));
    
    objs.push_back(std::make_shared<TurnModelScript>(m));
}
