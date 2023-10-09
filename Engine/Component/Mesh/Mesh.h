#pragma once
#include "../Component.h"
#include <vector>
#include "Header.h"
#include "Engine/Core/Vertex/Vertex.h"


class Mesh :public Component
{
public:
    /*  网格数据  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /*  函数  */
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<Texture>&& textures);
    void Draw(const ShaderProgram& shader);
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void setupMesh();
};  