#pragma once

class Component
{
public:
    bool operator==(Component* c);
    bool operator==(const char* c);
    virtual void Update() {}
    virtual void Start() {}
    virtual void Destory() {}
};

