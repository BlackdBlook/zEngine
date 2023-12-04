#include "Object.h"
#include "memory"
#include "../zEngine.h"
void* Object::operator new(size_t s)
{
    Object* obj = (Object*)malloc(s);
    obj->Object::Object();
    return obj;
}

Object::Object()
{
    SetPos(glm::vec3{0,0,0});
    SetRot(glm::vec3{0,0,0});
}

void Object::Start()
{
}

void Object::Update(float DeltaTime)
{
}

void Object::Draw()
{
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
