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
    void SetLevel(int index);
    static zEngine* GetInstance();
protected:


private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<Level> level = nullptr;

    void Update();
    void Draw();
    static zEngine* ins;
};


typedef zEngine Engine;