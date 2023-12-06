#pragma once
#include <memory>

class Object;

class Component
{
public:
    
    std::weak_ptr<Object> Parent;
    
    bool operator==(Component* c);
    bool operator==(const char* c);
    virtual void OnAttached();
    virtual void OnDettached();
    virtual void Draw() {}
    virtual void Update(float DeltaTime) {}
    virtual void Destory() {}
    virtual ~Component() = default; 
};

