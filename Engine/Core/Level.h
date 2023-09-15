#pragma once
#include <vector>
#include <memory>
class Object;

class Level
{
public:
    Level();
    virtual ~Level();
    void Update();
    void Draw();
    void Start();
    virtual void Init() {}
protected:
    std::vector<std::shared_ptr<Object>> objs;
};

