#include "BoxV3.h"
#include "Header.h"
#include "Engine/Core/Shader.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/DrawCommand/RenderCommandQueue.h"
#include "MeshData/Box/Mesh_Box.h"
#include "Objects/PointLight/PointLightV2.h"

static constexpr char indexChar[] = {'0','1','2','3'};

//#define LightColor 10.f

void BoxV3::initDirectLight()
{
    shader->setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader->setUniform("dirLight.color", glm::vec3{0.2f});
    shader->setUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader->setUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shader->setUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
}

void BoxV3::initPointLight(int index)
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

void BoxV3::updatePointLight(int index)
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

void BoxV3::initSpotLight()
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
    shader->setUniform("spotLight.cutOff",   glm::cos(glm::radians(30.0f)));
    shader->setUniform("spotLight.outerCutOff",   glm::cos(glm::radians(60.0f)));
}

void BoxV3::updateSpotLight()
{
    shader->setUniform("spotLight.position", Camera::GetCamera()->GetPos());
    shader->setUniform("spotLight.direction", Camera::GetCamera()->GetFont());
}

BoxV3::BoxV3() : Tex("container2.png"), specular("container2_specular.png")
{
    vao = 0;
    vbo = 0;
    shader = std::make_shared<ShaderProgram>("BoxV3");
}

BoxV3::BoxV3(const char* diff, const char* spec)
: Tex(diff), specular(spec)
{
    vao = 0;
    vbo = 0;
    shader = std::make_shared<ShaderProgram>("BoxV3");
}

void BoxV3::Start()
{
    Object::Start();


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BoxVertices), BoxVertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    shader->use();


    shader->setUniform("material.texture_diffuse0",0);
    shader->setUniform("material.texture_specular0",1);
    shader->setUniform("material.shininess", 32.0f);
    
    for(int i = 0;i < PointLight.size();i++)
    {
        initPointLight(i);
    }
    
    initDirectLight();

    initSpotLight();
    shader->setUniform("PointLightCount", (int)PointLight.size());
}

void BoxV3::Update(float DeltaTime)
{
    Object::Update(DeltaTime);

    shader->setUniform("model", GetModelMat());
}

void BoxV3::Draw()
{
    Object::Draw();

    shader->use();
    // mat4(view);
    // view = Camera::GetCamera()->GetCameraView();
    // shader->setUniform("view", view);
    //
    // shader->setUniform("projection", Camera::GetCamera()->GetCameraProjection());

    shader->setUniform("viewPos", Camera::GetCamera()->GetPos());

    for(int i = 0;i < PointLight.size();i++)
    {
        updatePointLight(i);
    }
    updateSpotLight();

    PushRenderCommand([this](RenderCommand& command)
    {
        command.vao = vao;
        command.vertexNum = 36;
        command.Shader = shader.get();
        command.DrawType = DrawType::DrawArrays;
        command.Textures.push_back(&Tex);
        command.Textures.push_back(&specular);
        command.WorldPos = GetPos();
    });
    
    // Tex.Bind();
    // specular.Bind(1);
    // glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    
}

BoxV3::~BoxV3()
{
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}

void BoxV3::addLight(std::shared_ptr<PointLightV2> light)
{
    PointLight.push_back(light);
}
