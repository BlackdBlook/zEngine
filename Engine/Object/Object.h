#pragma once
#include <memory>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
class Level;
class Component;


class Object
{
    glm::vec3 pos;
    glm::vec3 rot;

    std::vector<std::shared_ptr<Component>> Components;

public:
    Object();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void Draw();

    virtual void Attach(std::shared_ptr<Component> Target);
    virtual void Dettach(std::shared_ptr<Component> Target);

    
    virtual ~Object();
    void SetPos(glm::vec3 newPos);
    glm::vec3 GetPos();
    void SetRot(glm::vec3 newRot);
    glm::vec3 GetRot();
    static glm::mat4 getRotMat(glm::vec3 r);
};

