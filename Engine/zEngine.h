#pragma once
#include <vector>
#include <memory>
#include "Core/Level.h"
#include "Core/Camera/Camera.h"
struct GLFWwindow;
class zEngine;
class zEngine
{
public:
    void processInput(GLFWwindow* window);
    GLFWwindow* GetWindow();
    zEngine();
    void Run();
    void InitLevel();
    void SetLevel(int index);
    static zEngine* GetInstance();
protected:


private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<Level> level = nullptr;

    std::vector<std::function<void()>> levelList;

    void Update();
    void Draw();
    static zEngine* ins;
};


typedef zEngine Engine;