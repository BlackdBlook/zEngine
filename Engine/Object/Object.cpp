#include "Object.h"
#include "memory"
#include "../zEngine.h"
#include "Engine/Component/Component.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"

Object::Object()
{
    pos = glm::vec3{0,0,0};
    rot = glm::vec3{0,0,0};
    scale = glm::vec3{1,1,1};
    GetModelMat();
    Components = {};
}

void Object::Start()
{
    
}

void Object::Update(float DeltaTime)
{
    for(auto& c : Components)
    {
        c->Update(DeltaTime);
    }
}

void Object::Draw()
{
    for(auto& c : Components)
    {
        c->Draw();
    }
}

void Object::Attach(std::shared_ptr<Component> Target)
{
    if(!Target->Parent.expired())
    {
        auto oldParent = Target->Parent.lock();
        oldParent->Dettach(Target);
    }
    Target->Parent = Level::GetCurrentLevel()->GetObjectPtr(this); 
    Components.emplace_back(Target);
    Target->OnAttached();
}

void Object::Dettach(std::shared_ptr<Component> Target)
{
    auto it = Components.begin();
    
    while(it != Components.end())
    {
        if(*it == Target)
        {
            LOG(L"移除组件");
            Target->OnDettached();
            Components.erase(it);
            Target->Parent.reset();
            return;
        }
    }
    
    LOG(L"尝试移除不存在的组件");
    
}

Object::~Object()
{
}

void Object::SetPos(const glm::vec3& newPos)
{
    pos = newPos;
    needUpdateModelMat = true;
}

glm::vec3 Object::GetPos()
{
    return pos;
}



void Object::SetRot(const glm::quat& newRot)
{
    rot = newRot;
    needUpdateModelMat = true;
}

void AddRotateToQuat(glm::quat& quat, const glm::vec3 axis, float angle)
{
    quat *= glm::angleAxis(glm::radians(angle), axis);
}

void Object::SetRot(const glm::vec3& newRot)
{
    // 传入应为角度制
    rot = glm::vec3{0};
    AddRotateToQuat(rot, glm::vec3{0,0,1}, newRot.z);
    AddRotateToQuat(rot, glm::vec3{0,1,0}, newRot.y);
    AddRotateToQuat(rot, glm::vec3{1,0,0}, newRot.x);
    
    needUpdateModelMat = true;
}

void Object::AddRot(const glm::vec3& newRot)
{
    AddRotateToQuat(rot, glm::vec3{0,0,1}, newRot.z);
    AddRotateToQuat(rot, glm::vec3{0,1,0}, newRot.y);
    AddRotateToQuat(rot, glm::vec3{1,0,0}, newRot.x);
    
    needUpdateModelMat = true;
}

glm::quat Object::GetRot()
{
    return rot;
}

void Object::SetScale(const glm::vec3& newScale)
{
    scale = newScale;
    needUpdateModelMat = true;
}

glm::vec3 Object::GetScale()
{
    return scale;
}

glm::mat4 Object::GetModelMat()
{
    if(needUpdateModelMat)
    {
        needUpdateModelMat = false;
        
        mat4(m);

        // 平移
        m = glm::translate(m, pos);

        // 旋转
        glm::mat4 rotationMatrix = glm::mat4_cast(rot);
        m *= rotationMatrix;

        // 缩放
        m = glm::scale(m, scale);

        this->model = m;
    }

    return model;
}

