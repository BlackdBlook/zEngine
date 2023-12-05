#include "Object.h"
#include "memory"
#include "../zEngine.h"
#include "Engine/Component/Component.h"

Object::Object()
{
    SetPos(glm::vec3{0,0,0});
    SetRot(glm::vec3{0,0,0});
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

void Object::SetPos(glm::vec3 newPos)
{
    pos = newPos;
}

glm::vec3 Object::GetPos()
{
    return pos;
}

void Object::SetRot(glm::vec3 newRot)
{
    rot = newRot;
}

glm::vec3 Object::GetRot()
{
    return rot;
}

glm::mat4 Object::getRotMat(glm::vec3 r)
{
    mat4(ans);
    ans = glm::rotate(ans, glm::radians(r.x), glm::vec3(1, 0, 0));
    ans = glm::rotate(ans, glm::radians(r.y), glm::vec3(0, 1, 0));
    ans = glm::rotate(ans, glm::radians(r.z), glm::vec3(0, 0, 1));
    return ans;   
}
