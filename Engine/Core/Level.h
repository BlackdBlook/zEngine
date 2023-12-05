#pragma once
#include <vector>
#include <memory>
class Object;

class Level
{
public:
    Level();
    virtual ~Level();
    void Update(float DeltaTime);
    void Draw();
    void Start();
    virtual void Init() {}
    
    virtual std::shared_ptr<Object> NewObject();

    // 当前关卡的所有Object均存储在Level中
    std::shared_ptr<Object> GetObjectPtr(Object* Object);

    static Level* GetCurrentLevel();
protected:
    std::vector<std::shared_ptr<Object>> objs;
    static Level* CurrentLevel;
};
