#pragma once
#include <vector>
#include <memory>

#include "ToolKit/Typedef.h"
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
    template <class T, typename ...Args>
    std::shared_ptr<T> AddObject(Args&&... args) {
        // insert by perfectly forwarding into element at end, provide strong guarantee

        auto ptr = NewSPtr<T>(args...);

        objs.push_back(ptr);
        
        return ptr;
    }
    
    static Level* CurrentLevel;
};
