#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>&& vertices
    , std::vector<unsigned int>&& indices
    , std::vector<Texture2D>&& diffuseTextures
    , std::vector<Texture2D>&& specularTextures)
{
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->diffuseTextures = std::move(diffuseTextures);
    this->specularTextures = std::move(specularTextures);

    setupMesh();
}

Mesh::Mesh(Mesh&& mesh) noexcept
{
    vertices = std::move(mesh.vertices);
    indices = std::move(mesh.indices);
    diffuseTextures = std::move(mesh.diffuseTextures);
    specularTextures = std::move(mesh.specularTextures);
    VAO = mesh.VAO;
    VBO = mesh.VBO;
    EBO = mesh.EBO;
}

void Mesh::Draw(ShaderProgram* shader)
{
    static const size_t size = 4;
    char* number = new char[size];
    for(int i = 0; i < diffuseTextures.size(); i++)
    {
        // 获取纹理序号（diffuse_textureN 中的 N）
        sprintf_s(number, size, "%d", i);
        const char* name = "texture_diffuse";
        static const std::string ms = "material.";
        const std::string unifrom = (ms + name + number);
        diffuseTextures[i].Bind(i);
        shader->setUniform(unifrom.c_str(), i);
    }

    const int diffNum = (int)diffuseTextures.size();
    for(int i = 0;i < specularTextures.size();i++)
    {
        // 获取纹理序号（diffuse_textureN 中的 N）
        sprintf_s(number, size, "%d", i);
        const char* name = "texture_specular";
        static const std::string ms = "material.";
        const std::string unifrom = (ms + name + number);
        specularTextures[i].Bind(diffNum + i);
        shader->setUniform(unifrom.c_str(), diffNum + i);
    }

    delete[] number;

    shader->use();
    glActiveTexture(GL_TEXTURE0);

    // 绘制网格
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);   
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}  