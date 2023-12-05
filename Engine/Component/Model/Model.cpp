#include "Model.h"
#include "assimp/material.h"
#include "assimp/texture.h"
#include "Header.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/TextureAssimp/TextureAssimp.h"
#include "Engine/SubSystem/AssetSystem.h"
#include "ToolKit/stb_img.h"


Model::Model(const std::string& MeshName, const std::shared_ptr<ShaderProgram>& shader_program)
: name(MeshName), shader_program(shader_program)
{
    loadModel();
}

Model::Model(std::string&& MeshName, const std::shared_ptr<ShaderProgram>& shader_program)
: name(std::move(MeshName)), shader_program(shader_program)
{
    loadModel();
}

std::shared_ptr<ShaderProgram> Model::GetShaderProgram()
{
    return shader_program;
}

void Model::Draw()
{
    const auto P = Parent.lock();

    mat4(view);
    view = Camera::GetCamera()->GetCameraView();
    shader_program->setUniform("view", view);


    mat4(model);
    model = glm::translate(model, P->GetPos());
 
    model *= Object::getRotMat(P->GetRot());
    shader_program->setUniform("model", model);

    mat4(projection);
    projection = glm::perspective(
        glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);

    shader_program->setUniform("projection", projection);
    shader_program->setUniform("viewPos", Camera::GetCamera()->GetPos());

    for(auto& m : meshes)
    {
        m.Draw(shader_program.get());
    }
}

void Model::loadModel()
{
    Assimp::Importer importer;

    std::string path = AssetSystem::GetInstance()->GetFilePathByName(name);
    
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG("Error Assimp : \n\t", importer.GetErrorString(), "\n", name);
    }
    
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));         
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    vertices.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex& vertex = vertices.emplace_back();
        // 处理顶点位置、法线和纹理坐标

        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
            {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        
    }
    
    // 处理索引
    indices.reserve(mesh->mNumFaces);
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    // 处理材质
    std::vector<Texture2D> diffuseMaps {};
    std::vector<Texture2D> specularMaps{};
    if(mesh->mMaterialIndex > 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
    }

    return Mesh(std::move(vertices), std::move(indices)
        , std::move(diffuseMaps), std::move(specularMaps));
}

std::vector<Texture2D> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    std::vector<Texture2D> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        // 拿到图的名称
        mat->GetTexture(type, i, &str);
        Texture2D t = textures.emplace_back(str.C_Str());
    }
    return textures;
}

void Model::Update(float DeltaTime)
{
    Component::Update(DeltaTime);
}
