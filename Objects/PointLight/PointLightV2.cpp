#include "PointLightV2.h"
#include "PointLight.h"
#include "Engine/zEngine.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/DrawCommand/RenderCommandQueue.h"
#include "MeshData/Box/Mesh_Box.h"

void PointLightV2::Init()
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

#define MOVE_SPEED 10

void PointLightV2::Update(float DeltaTime)
{
    glm::vec3 pos = GetPos();
    const float MoveSpeed = MOVE_SPEED * DeltaTime;
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,0,-MoveSpeed);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,0,MoveSpeed);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        pos += glm::vec3(-MoveSpeed, 0, 0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        pos += glm::vec3(MoveSpeed, 0, 0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,MoveSpeed,0);
    }
    if (glfwGetKey(Engine::GetInstance()->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        pos+= glm::vec3(0,-MoveSpeed,0);
    }
    if(GetPos() != pos)
    {
        SetPos(pos);
    }
}

void PointLightV2::Draw()
{
    shader->use();
    MAT4(model);
    
    model = glm::translate(model,GetPos());
    model = glm::scale(model, glm::vec3(0.5));
    shader->setUniform("model", model);
    shader->setUniform("view", Camera::GetCamera()->GetCameraView());
    shader->setUniform("projection", Camera::GetCamera()->GetCameraProjection());
    // glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    PushRenderCommand([this](RenderCommand& command)
    {
        command.vao = vao;
        command.vertexNum = 36;
        command.Shader = shader.get();
        command.DrawType = DrawType::DrawArrays;
        command.WorldPos = GetPos();
    });
}

PointLightV2::PointLightV2(glm::vec3 pos)
{
    SetPos(pos);
    Init();
}

PointLightV2::~PointLightV2()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
