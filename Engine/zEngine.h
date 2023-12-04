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
    zEngine();
    GLFWwindow* GetWindow();
    void Run();
    void SetLevel(int index);
    float GetDeltaTime();
    static zEngine* GetInstance();

protected:
    void InitLevel();
    void InitInput();
    void processInput(GLFWwindow* window);

private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<Level> level = nullptr;
    float DeltaTime = 0;
    std::vector<std::function<void()>> levelList;

    void Update();
    void Draw();
    static zEngine* ins;
};

typedef zEngine Engine;