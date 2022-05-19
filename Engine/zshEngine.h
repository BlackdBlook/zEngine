#pragma once
#include <vector>
#include <memory>
#include "Core/Level.h"
#include "Core/Camera/Camera.h"
struct GLFWwindow;

class zshEngine
{
public:
    void processInput(GLFWwindow* window);
    zshEngine();
    void Run();
    void SetLevel(int index);
protected:


private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<Level> level = nullptr;

    void Update();
    void Draw();
    
};


typedef zshEngine Engine;