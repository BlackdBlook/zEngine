#include "BoxV4.h"

#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/DrawCommand/RenderCommandQueue.h"
#include "MeshData/Box/Mesh_Box.h"

BoxV4::BoxV4() :
Tex("container2.png"),
Tex2("container2_specular.png")
{
    shader = NewSPtr<ShaderProgram>("MeshLightWithUbo");
    
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
}

void BoxV4::OnAttached()
{
    Component::OnAttached();
}

void BoxV4::OnDettached()
{
    Component::OnDettached();
}

void BoxV4::Draw()
{
    Component::Draw();
    shader->setUniform("model", Parent.lock()->GetModelMat());
    PushRenderCommand([this](RenderCommand& command)
    {
        command.vao = vao;
        command.vertexNum = 36;
        command.Shader = shader.get();
        command.DrawType = DrawType::DrawArrays;
        command.Textures.push_back(&Tex);
        command.Textures.push_back(&Tex2);
        command.TargetObject = Parent.lock().get();
    });
}

void BoxV4::Update(float DeltaTime)
{
    Component::Update(DeltaTime);
}

void BoxV4::Destory()
{
    Component::Destory();
}

BoxV4::~BoxV4()
{
}
