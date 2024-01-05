#include "PointLightWithUbo.h"

#include "Engine/Core/DrawCommand/RenderCommandQueue.h"
#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"
#include "MeshData/Box/Mesh_Box.h"

uint8 PointLightWithUbo::PointLightGlobalMask = 0;

static constexpr char indexChar[] = {'0','1','2','3'};
void PointLightWithUbo::initPointLight(int mask)
{
    const std::string s = GetUniformObjectName(mask);

    SetGlobalUniformBuffer("LightData",
        s +"strength",  1.f);
    SetGlobalUniformBuffer("LightData",
        s +"color",  color);
    SetGlobalUniformBuffer("LightData",
        s +"ambient", ambient);
    SetGlobalUniformBuffer("LightData",
        s +"diffuse", diffuse);
    SetGlobalUniformBuffer("LightData",
        s +"specular", specular);
    SetGlobalUniformBuffer("LightData",
        s +"constant",  constant);
    SetGlobalUniformBuffer("LightData",
        s +"linear",    linear);
    SetGlobalUniformBuffer("LightData",
        s +"quadratic", quadratic);
}

void PointLightWithUbo::updatePointLight(int index)
{
    // if(index > 3)
    // {
    //     LOG("错误，光源类型不能超过4个");
    // }
    // auto pos = PointLight[index]->GetPos();
    //
    // std::string s = "pointLights[";
    // s += indexChar[index];
    //
    // shader->setUniform((s + "].position").c_str(), pos);
}

std::string PointLightWithUbo::GetUniformObjectName(uint8 Mask)
{
    switch(Mask)
    {
    case 1 << 0:
        return "pointLights[0].";
    case 1 << 1: 
        return "pointLights[1].";
    case 1 << 2:
        return "pointLights[2].";
    case 1 << 3:
        return "pointLights[3].";
    default:
        LOG("Error Point Light Index");
        return "";
    }
}

PointLightWithUbo::PointLightWithUbo()
{
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

    sp = NewSPtr<ShaderProgram>("pointLight");
}

void PointLightWithUbo::OnAttached()
{


    if(PointLightGlobalMask == 0b00001111)
    {
        LOG("Point Light Overflow");
        assert(false);
        return;
    }
    uint8 mask = 1;
    for(int i = 0;i < 8;i++)
    {
        if((PointLightGlobalMask & mask) == 0)
        {
            PointLightGlobalMask |= mask;
            break;
        }
        mask <<= 1;
    }
    PointLightIndexMask = mask;

    LightComponent::OnAttached();
}

void PointLightWithUbo::OnDettached()
{
    LightComponent::OnDettached();

    PointLightGlobalMask ^= PointLightIndexMask;
}

void PointLightWithUbo::Draw()
{
    LightComponent::Draw();
    sp->setUniform("model", Parent.lock()->GetModelMat());
    PushRenderCommand([this](RenderCommand& command)
    {
        command.vao = vao;
        command.vertexNum = 36;
        command.Shader = sp.get();
        command.DrawType = DrawType::DrawArrays;
        command.WorldPos = GetPos();
    });
}

void PointLightWithUbo::InitLightBuffer()
{
    initPointLight(PointLightIndexMask);
}

void PointLightWithUbo::UpdateLightBuffer()
{
    const std::string s = GetUniformObjectName(PointLightIndexMask);
    SetGlobalUniformBuffer("LightData",
        s +"position",  GetPos());
}

void PointLightWithUbo::DisableLight()
{
    const std::string s = GetUniformObjectName(PointLightIndexMask);
    SetGlobalUniformBuffer("LightData",
        s +"strength",  0.f);
}
