#include "PointLightV3.h"

#include "PointLightV2.h"
#include "Engine/Core/Camera/Camera.h"


PointScript::PointScript(std::shared_ptr<ShaderProgram> sp, bool EnableMoveLight): TargetShader (sp), EnableMoveLight(EnableMoveLight)
{
    PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{-3,3,0}));
    PointLight.emplace_back(std::make_shared<PointLightV2>(glm::vec3{5,3,0}));
    sp->setUniform("material.shininess", 32.f);

    auto shader = this->TargetShader.lock();
    shader->use();
    //initDirectLight();
        
    for(int i = 0;i < PointLight.size();i++)
    {
        initPointLight(i);
    }
    initSpotLight();
}

void PointScript::initDirectLight()
{
    auto shader = this->TargetShader.lock();
    shader->setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader->setUniform("dirLight.ambient", glm::vec3{0.4f});
    shader->setUniform("dirLight.diffuse", glm::vec3{0.4f});
    shader->setUniform("dirLight.specular", glm::vec3{0.5f});
}

void PointScript::initPointLight(int index)
{
    auto shader = this->TargetShader.lock();
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

void PointScript::updatePointLight(int index)
{
    if(index > 3)
    {
        LOG("错误，光源类型不能超过4个");
    }
    auto pos = PointLight[index]->GetPos();
        
    std::string s = "pointLights[";
    s += indexChar[index];
    auto shader = this->TargetShader.lock();
    shader->setUniform((s + "].position").c_str(), pos);
}

void PointScript::initSpotLight()
{
    auto shader = this->TargetShader.lock();
    shader->setUniform("spotLight.constant",  1.0f);
    // 衰减强度
    shader->setUniform("spotLight.linear",    0.0014f);
    // 二次衰减强度
    shader->setUniform("spotLight.quadratic", 0.000007f);
    shader->setUniform("spotLight.color",  glm::vec3{1});
    shader->setUniform("spotLight.ambient",  glm::vec3{0});
    shader->setUniform("spotLight.diffuse",  glm::vec3{1}); // 将光照调暗了一些以搭配场景
    shader->setUniform("spotLight.specular", glm::vec3{1});
    shader->setUniform("spotLight.cutOff",   glm::cos(glm::radians(30.0f)));
    shader->setUniform("spotLight.outerCutOff",   glm::cos(glm::radians(60.f)));
}

void PointScript::updateSpotLight()
{
    auto shader = this->TargetShader.lock();
    shader->setUniform("spotLight.position", Camera::GetCamera()->GetPos());
    shader->setUniform("spotLight.direction", Camera::GetCamera()->GetFont());
}

void PointScript::Update(float DeltaTime)
{
    if(EnableMoveLight)
    {
        PointLight[0]->Update(DeltaTime);
        PointLight[1]->Update(DeltaTime);   
    }
    Camera::GetCamera()->Update(DeltaTime);
}

void PointScript::Draw()
{
    updateSpotLight();
    for(int i = 0;i < PointLight.size();i++)
    {
        updatePointLight(i);
        PointLight[0]->Draw();
        PointLight[1]->Draw();
    }
        
}
