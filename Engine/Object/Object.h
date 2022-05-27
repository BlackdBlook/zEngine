#pragma once
#include <glm/vec3.hpp>
class Object
{
    glm::vec3 pos;
    glm::vec3 rot;

public:
    void* operator new(size_t s);
    Object();
    virtual void Start();
    virtual void Update();
    virtual void Draw();
    virtual ~Object();
    void SetPos(glm::vec3 newPos);
    glm::vec3 GetPos();
    void SetRot(glm::vec3 newRot);
    glm::vec3 GetRot();
};

