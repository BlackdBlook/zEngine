#include "SkyBox.h"

#include "Engine/SubSystem/AssetSystem.h"
#include "Levels/DrawTexBox/DrawTexBox.h"
#include "MeshData/Box/Mesh_Box.h"
#include "ToolKit/stb_img.h"

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::string path = AssetSystem::GetInstance()->GetFilePathByName(faces[i]);
        LOG(path);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


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
    cubemapTexture = loadCubemap(faces);
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
    // auto view = Camera::GetCamera()->GetCameraView();
    // view = glm::mat4(glm::mat3(Camera::GetCamera()->GetCameraView()));
    // shader->setUniform("view", view);
    // shader->setUniform("projection",Camera::GetCamera()->GetCameraProjection());
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

SkyBox::~SkyBox()
{
}
