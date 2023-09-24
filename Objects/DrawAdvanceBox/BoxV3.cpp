#include "BoxV3.h"
#include "Header.h"
#include "Engine/Core/Camera/Camera.h"
#include "Mesh/Box/Mesh_Box.h"
#include "Objects/PointLightV2.h"

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
    

    Tex = Texture2D("container2.png");
    specular = Texture2D("container2_specular.png");
    upTex = Texture2D("matrix.jpg");
    shader->setUniform("material.diffuse",0);
    shader->setUniform("material.specular",1);
    shader->setUniform("material.specular", 0.5f, 0.5f, 0.5f);
    shader->setUniform("material.shininess", 32.0f);
    shader->setUniform("UpTex",2);
    shader->setUniform("Light.constant",  1.0f);
    // 衰减强度
    shader->setUniform("Light.linear",    0.0014f);
    // 二次衰减强度
    shader->setUniform("Light.quadratic", 0.000007f);
    shader->setUniform("Light.color",  1.f, 1.f, 1.f);
    shader->setUniform("Light.ambient",  0.2f, 0.2f, 0.2f);
    shader->setUniform("Light.diffuse",  1.5f, 1.5f, 1.5f); // 将光照调暗了一些以搭配场景
    shader->setUniform("Light.specular", 1.0f, 1.0f, 1.0f);
    shader->setUniform("Light.cutOff",   glm::cos(glm::radians(25.5f)));
    shader->setUniform("Light.outerCutOff",   glm::cos(glm::radians(30.5f)));
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
    shader->setUniform("view", view);

    mat4(projection);
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
    shader->setUniform("projection", projection);
    
    shader->setUniform("Time", (float)glfwGetTime());
    

    shader->setUniform("Light.position", Light->GetPos());
    shader->setUniform("Light.direction", -Camera::GetCamera()->GetFont());
    

    shader->setUniform("viewPos", Camera::GetCamera()->GetPos());
    shader->use();
    Tex.Bind();
    specular.Bind(1);
    upTex.Bind(2);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
}

BoxV3::~BoxV3()
{
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}

void BoxV3::setLight(std::shared_ptr<PointLightV2> light)
{
    Light = light;
}
