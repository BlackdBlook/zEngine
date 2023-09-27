#include "BoxV3.h"
#include "Header.h"
#include "Engine/Core/Camera/Camera.h"
#include "Mesh/Box/Mesh_Box.h"
#include "Objects/PointLightV2.h"

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
    auto pos = PointLight[index]->GetPos();
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
    shader->setUniform("spotLight.cutOff",   glm::cos(glm::radians(10.0f)));
    shader->setUniform("spotLight.outerCutOff",   glm::cos(glm::radians(15.0f)));
}

void BoxV3::updateSpotLight()
{
    shader->setUniform("spotLight.position", Camera::GetCamera()->GetPos());
    shader->setUniform("spotLight.direction", -Camera::GetCamera()->GetFont());
}

BoxV3::BoxV3()
{
    vao = 0;
    vbo = 0;
}

void BoxV3::Start()
{
    Object::Start();

    shader = std::make_shared<ShaderProgram>("BoxV3");

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

    Tex = Texture2D("container2.png");
    specular = Texture2D("container2_specular.png");
    shader->setUniform("material.diffuse",0);
    shader->setUniform("material.specular",1);
    shader->setUniform("material.shininess", 32.0f);

    for(int i = 0;i < PointLight.size();i++)
    {
        initPointLight(i);
    }
    
    initDirectLight();

    initSpotLight();
    shader->setUniform("PointLightCount", (int)PointLight.size());
}

void BoxV3::Update()
{
    Object::Update();
    //double lerp = (sin(glfwGetTime())) / 2.0f + 0.5;
    double lerp = glfwGetTime() / 5.0f;
    mat4(model);
    model = glm::translate(model, GetPos());
    const glm::vec3 rot = GetRot();
    
    model = glm::rotate(model,
     glm::radians(rot.x),
     glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model,
        glm::radians(rot.y),
        glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model,
        glm::radians(rot.z),
        glm::vec3(0.0, 0.0, 1.0));
    shader->setUniform("model", model);
}

void BoxV3::Draw()
{
    Object::Draw();
    mat4(view);
    view = Camera::GetCamera()->GetCameraView();

    shader->use();
    shader->setUniform("view", view);

    mat4(projection);
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
    shader->setUniform("projection", projection);

    shader->setUniform("viewPos", Camera::GetCamera()->GetPos());

    for(int i = 0;i < PointLight.size();i++)
    {
        updatePointLight(i);
    }
    updateSpotLight();
    
    Tex.Bind();
    specular.Bind(1);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
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
