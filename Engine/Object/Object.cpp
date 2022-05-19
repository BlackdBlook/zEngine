#include "Object.h"
#include "memory"
#include "../zshEngine.h"
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
