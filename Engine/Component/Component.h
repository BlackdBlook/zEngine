#pragma once
#include <memory>

class Object;

class Component
{
    friend Object;
protected:
    std::weak_ptr<Object> Parent;
    
public:
    bool operator==(Component* c);
    bool operator==(const char* c);
    virtual void OnAttached();
    virtual void OnDettached();
    virtual void Draw() {}
    virtual void Update(float DeltaTime) {}
    virtual void Start() {}
    virtual void Destory() {}
    virtual ~Component() = default; 
};

