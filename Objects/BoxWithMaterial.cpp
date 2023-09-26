#include "BoxWithMaterial.h"
#include "Engine/Core/Camera/Camera.h"
#include "PointLight.h"
#include "Engine/SubSystem/AssetSystem.h"
#include "Mesh/Box/Mesh_Box.h"


BoxWithMaterial::BoxWithMaterial()
{
    vao = 0;
    vbo = 0;
}

void BoxWithMaterial::Start()
{
    Object::Start();
    shader = std::make_shared<ShaderProgram>("BoxWithMat");


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
    shader->setUniform("UpTex",2);

    shader->setUniform("material.shininess", 32.0f);
    shader->setUniform("light.color",  1.f, 1.f, 1.f);
    shader->setUniform("light.ambient",  0.2f, 0.2f, 0.2f);
    shader->setUniform("light.diffuse",  1.5f, 1.5f, 1.5f); // 将光照调暗了一些以搭配场景
    shader->setUniform("light.specular", 1.0f, 1.0f, 1.0f); 
}

void BoxWithMaterial::Update()
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

void BoxWithMaterial::Draw()
{
    Object::Draw();
    mat4(view);
    view = Camera::GetCamera()->GetCameraView();
    shader->setUniform("view", view);

    mat4(projection);
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
    shader->setUniform("projection", projection);
    
    //shader->setUniform("Time", (float)glfwGetTime());
    
    //shader->setUniform("material.specular", 0.5f, 0.5f, 0.5f);

    shader->setUniform("light.position", Light->GetPos());
    shader->setUniform("viewPos", Camera::GetCamera()->GetPos());
    shader->use();
    Tex.Bind();
    specular.Bind(1);
    upTex.Bind(2);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
}

BoxWithMaterial::~BoxWithMaterial()
{
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}

void BoxWithMaterial::setLight(std::shared_ptr<PointLight> light)
{
    Light = light;
}
