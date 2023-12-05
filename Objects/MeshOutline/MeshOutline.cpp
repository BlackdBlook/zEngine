#include "MeshOutline.h"

#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"


MeshOutline::MeshOutline(const char* modelName, std::shared_ptr<ShaderProgram> shader)
    :Model(modelName, shader)
{
    sp = std::make_shared<ShaderProgram>("MeshOutLine");
}

void MeshOutline::Draw()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
    glStencilMask(0xFF); // 启用模板缓冲写入

    Model::Draw();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    
    glDisable(GL_DEPTH_TEST);
    
    const auto P = Parent.lock();
    
    mat4(view);
    view = Camera::GetCamera()->GetCameraView();
    sp->setUniform("view", view);
    
    
    mat4(model);
    model = glm::translate(model, P->GetPos() - glm::vec3{ 0, 0.6f, 0});
    
    model *= Object::getRotMat(P->GetRot());
    
    model = glm::scale(model, glm::vec3{1 + OutlineSize});
    
    sp->setUniform("model", model);
    
    mat4(projection);
    projection = glm::perspective(
        glm::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
    
    sp->setUniform("projection", projection);
    
    sp->setUniform("viewPos", Camera::GetCamera()->GetPos());
    
    for(auto& m : meshes)
    {
        m.Draw(sp.get());
    }
    
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST); 
}
