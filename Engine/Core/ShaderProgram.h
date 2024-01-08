#pragma once
#include"../../ToolKit/Typedef.h"
#include <map>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

enum class BlendType
{
    Opaque,
    Translucent,
    Mask,
    Skybox
};

enum class BlendType;
class Shader;
class ShaderProgram
{
    GLID programID;
    std::unordered_map<std::string, GLID> uniformCache;

    GLID getUniformFromCache(const std::string& name);


    std::string shaderNameVer;
    std::string shaderNameFar;
    
    void init(std::string&& ver,std::string&& far);
    void link();
    void Attach(Shader& s);
    void RegistGlobalUniformBlock();
    void BindShadowMap();

public:

    // 使用方式详见GlobalUniformBuffer.cpp
    void showAllActiveUnifrom();
    std::vector<std::string> GetAllUniformBlockName();
    void GetAllUniformBlockName(std::vector<std::string>& out);
    GLsizei glGetActiveUniformBlockSize(GLID blockIndex);
    GLID GetUniformBlockIndex(const std::string& s);
    GLint GetUniformBlockMemberNumbers(GLID blockIndex);
    std::string GetUniformBlockMemberName(GLID UniformBlockMemberId);
    GLint GetUniformBlockMemberSize(GLID UniformBlockMemberId);
    GLint GetUniformBlockMemberOffset(GLID UniformBlockMemberId);
    GLenum GetUniformBlockMemberType(GLID UniformBlockMemberId);
    void GetUniformBlockMemberId(
        GLint number, GLID BlockNumberId, std::vector<GLID>& Ids);
    
    BlendType BlendType = BlendType::Opaque;
    std::string GetName();
    
    inline void use();
    GLID getProgramID(){return programID;}


    ShaderProgram() = delete;
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram(const ShaderProgram& other);
    ShaderProgram(std::string&& ver);
    ShaderProgram(std::string&& ver,std::string&& far);
    void operator+=(Shader& s);


    
    void setUniform(const char* name,float x);
    void setUniform(const char* name,int x);
    void setUniform(const char* name, const glm::vec3& x);
    void setUniform(const char* name, const glm::mat4& x);
    void setUniform(const char* name, float x, float y, float z);
    void setUniform(const char* name, float x, float y, float z, float w);
    ~ShaderProgram();
};

