#include "SkyBox.h"

#include "Engine/SubSystem/AssetSystem.h"
#include "Levels/DrawTexBox/DrawTexBox.h"
#include "MeshData/Box/Mesh_Box.h"
#include "ToolKit/stb_img.h"

void SkyBox::Start()
{
    Object::Start();
    std::vector<std::string> faces
    {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    cubemapTexture = TextureCube(faces);
    shader = NewSPtr<ShaderProgram>("SkyBox");
    shader->setUniform("skybox",0);
    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SkyBoxVertices), &SkyBoxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void SkyBox::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
}

void SkyBox::Draw()
{
    Object::Draw();
    //glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    shader->use();
    glBindVertexArray(skyboxVAO);
    cubemapTexture.use();
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

SkyBox::~SkyBox()
{
}
