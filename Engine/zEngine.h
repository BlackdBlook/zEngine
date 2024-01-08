#pragma once
#include <vector>
#include <memory>
#include "Core/Level.h"
#include "Core/Camera/Camera.h"
#include "Core/FrameBuffer/FrameBuffer.h"
#include "Core/TextureSceneDepth/SceneDepthFrameBuffer.h"
class LightSystem;
class ScreenProcessingManager;
struct GLFWwindow;
class zEngine;
class zEngine
{
public:
    inline static uint32 WindowX = 2560;
    inline static uint32 WindowY = 1440;


    
    zEngine();
    GLFWwindow* GetWindow();
    void Run();
    void SetLevel(int index);
    float GetDeltaTime();
    SPtr<ScreenProcessingManager> GetScreenProcessingManagerPtr();
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
    SPtr<ScreenProcessingManager> ScreenProcessingManagerPtr;

    void Update();
    void DrawPreProcessing();
    void DrawPostProcessing();
    void DrawShadowMap();
    void Draw();


    static zEngine* ins;
};

typedef zEngine Engine;