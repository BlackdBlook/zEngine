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

}

void Object::Start()
{
}

void Object::Update()
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
