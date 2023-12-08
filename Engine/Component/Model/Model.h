#pragma once
#include <string>
#include <vector>
#include <Engine/Core/TextureAssimp/TextureAssimp.h>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Engine/Component/Mesh/Mesh.h"
#include "Engine/Object/Object.h"

class Model : public Component
{
public:
    Model(const std::string& name, const std::shared_ptr<ShaderProgram>& shader_program);
    explicit Model(std::string&& name, const std::shared_ptr<ShaderProgram>& shader_program);
    std::shared_ptr<ShaderProgram> GetShaderProgram();
    virtual void OnAttached() override;
    virtual void OnDettached() override;
protected:
    // std::unordered_map<std::string, Texture2D> loadedTex;
    std::string name;
    std::vector<Mesh> meshes;
    std::shared_ptr<ShaderProgram> shader_program;
        
    void loadModel();

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture2D> loadMaterialTextures(aiMaterial *mat, aiTextureType type);

public:
    void Update(float DeltaTime) override;
    void Draw() override;
};
