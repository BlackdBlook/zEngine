#include "SpotLight.h"

#include "Engine/zEngine.h"
#include "MeshData/Box/Mesh_Box.h"

void SpotLight::Init()
{
    shader = std::make_shared<ShaderProgram>
        ("pointLight", "pointLight");
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);


    glBufferData(GL_ARRAY_BUFFER,sizeof(BoxVertices),BoxVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),nullptr);

    glEnableVertexAttribArray(0);
}

#define MOVE_SPEED 0.001

void SpotLight::Update(float DeltaTime)
{
    glm::vec3 pos = GetPos();
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,MOVE_SPEED,0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,-MOVE_SPEED,0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,0,MOVE_SPEED);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,0,-MOVE_SPEED);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        pos += glm::vec3(MOVE_SPEED, 0, 0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        pos += glm::vec3(-MOVE_SPEED, 0, 0);
    }
    SetPos(pos);
}

void SpotLight::Draw()
{
    shader->use();
    mat4(model);
    mat4(view);
    mat4(projection);
    model = glm::translate(model, GetPos());
    model = glm::scale(model, glm::vec3(0.5));
    shader->setUniform("model", model);
    
    model = glm::translate(model,GetPos());
    model = glm::scale(model, glm::vec3(0.5));
    shader->setUniform("model", model);
    view = Camera::GetCamera()->GetCameraView();
    shader->setUniform("view", view);
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
    shader->setUniform("projection", projection);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

SpotLight::SpotLight(glm::vec3 pos)
{
    SetPos(pos);
    Init();
}

SpotLight::~SpotLight()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
