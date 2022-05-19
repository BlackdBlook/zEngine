#pragma once
#include <glm/vec3.hpp>
class Object
{
    glm::vec3 pos;
public:
    void* operator new(size_t s);
    Object();
    virtual void Start();
    virtual void Update();
    virtual void Draw();
    virtual ~Object();
};

