#include "DrawNanosuit.h"

#include <memory>

#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Objects/PointLightV2.h"

DrawNanosuit::~DrawNanosuit()
{
}

class PointScript : public Object
{
    static constexpr char indexChar[] = {'0','1','2','3'};
    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<PointLightV2> PointLight[4];
public:
    PointScript(std::shared_ptr<ShaderProgram> sp): shader (sp)
    {
        PointLight[0] = std::make_shared<PointLightV2>(glm::vec3{19,0,0});
    }
    void Start() override
    {
        initDirectLight();
        shader->setUniform("PointLightCount", 1);
        initPointLight(0);
        initSpotLight();
    }

    void initDirectLight()
    {
        shader->use();
        shader->setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader->setUniform("dirLight.color", glm::vec3{0.2f});
        shader->setUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        shader->setUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader->setUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
    }

    void initPointLight(int index)
    {
        if(index > 4)
        {
            LOG("错误，光源类型不能超过4个");
        }
        std::string s = "pointLights[";
        s += indexChar[index];
        
        shader->setUniform((s +"].color").c_str(),  glm::vec3{1});
        shader->setUniform((s +"].ambient").c_str(),    0.05f, 0.05f, 0.05f);
        shader->setUniform((s +"].diffuse").c_str(),     0.8f, 0.8f, 0.8f);
        shader->setUniform((s +"].specular").c_str(),    1.0f, 1.0f, 1.0f);
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
        shader->setUniform("spotLight.color",  glm::vec3{1});
        shader->setUniform("spotLight.ambient",  glm::vec3{0});
        shader->setUniform("spotLight.diffuse",  glm::vec3{1}); // 将光照调暗了一些以搭配场景
        shader->setUniform("spotLight.specular", glm::vec3{1});
        shader->setUniform("spotLight.cutOff",   glm::cos(glm::radians(10.0f)));
        shader->setUniform("spotLight.outerCutOff",   glm::cos(glm::radians(15.0f)));
    }

    void updateSpotLight()
    {
        shader->setUniform("spotLight.position", Camera::GetCamera()->GetPos());
        shader->setUniform("spotLight.direction", -Camera::GetCamera()->GetFont());
    }

    
    void Update() override
    {
        PointLight[0]->Update();
        Camera::GetCamera()->Update();
        updatePointLight(0);
        updateSpotLight();
    }
    void Draw() override
    {
        PointLight[0]->Draw();
    }
    ~PointScript() override = default;
};

void DrawNanosuit::Init()
{
    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(20,0,0));
    Camera::GetCamera()->SetFont(glm::vec3(1,0,0));
    
    std::string name = std::string{"nanosuit.obj"};
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("BoxV3");

    auto m = std::make_shared<Model>(std::move(name), sp);
    m->SetPos(glm::vec3{0,-10,0});
    m->SetRot(glm::vec3{0,90,0});
    objs.push_back(m);

    objs.push_back(std::make_shared<PointScript>(sp));

    
    // objs.push_back(std::make_shared<PointLightV2>(glm::vec3{0, 0, 0}));
}
