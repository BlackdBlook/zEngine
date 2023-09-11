#pragma once
#include <vector>
#include <memory>
class Object;

class Level
{
public:
    Level();
    virtual ~Level();
    void Start();
    void Update();
    void Draw();
    virtual void Init() {}
protected:
    std::vector<std::shared_ptr<Object>> objs;
};

