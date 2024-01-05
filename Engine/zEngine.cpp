#include "zEngine.h"

#include <thread>

#include "../ToolKit/GLLib.h"
#include "../Levels/DrawSJX/DrawSanjiaoxing.h"
#include "../Levels/DrawRTSJX/DrawRTSJX.h"
#include "../Levels/DrawBox/DrawBox.h"
#include "../Levels/DrawTexBox/DrawTexBox.h"
#include "../Levels/BoxWithLight/DrawBoxWithLight.h"
#include <GLFW/glfw3.h>

#include "../Levels/TexBoxWithLight/DrawTexBoxWithLight.h"
#include "Core/DrawCommand/RenderCommandQueue.h"
#include "Core/FrameBuffer/FrameBuffer.h"
#include "Core/InputSystem/InputSystem.h"
#include "Core/ScreenProcessingManager/ScreenProcessingManager.h"
#include "Levels/BoxWithMat/DrawBoxWithMat.h"
#include "Levels/DrawAdvanceLight/DrawAdvanceLight.h"
#include "Levels/DrawBlend/DrawBlend.h"
#include "Levels/DrawDepthTestBuffer/DrawDepthTestBuffer.h"
#include "Levels/DrawFreamBuffer/DrawFrameBuffer.h"
#include "Levels/DrawShadow/DrawShadow.h"
#include "Levels/DrawSkyBox/DrawSkyBox.h"
#include "Levels/DrawStencilTest/DrawStencilTest.h"
#include "Levels/NanoSuit0/DrawNanosuit.h"
#include "SubSystem/AssetSystem.h"
#include "ToolKit/TimerToolkit.h"

#define makeLevel(s) \
level.reset();\
level = std::shared_ptr<s>(new s());\
level->Init();\
level->Start()

#define addLevel(s) \
levelList.emplace_back([this]() \
{                               \
    makeLevel(s);               \
})                              

zEngine* zEngine::ins = nullptr;

void zEngine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        GLenum error = glGetError();
        LOG(error);
    }
    
    for (int i = GLFW_KEY_0; i < GLFW_KEY_0 + levelList.size() + 1; i++)
    {
        if (glfwGetKey(window, i) == GLFW_PRESS)
        {
            SetLevel(i - GLFW_KEY_0);
        }
    }
}
GLFWwindow* zEngine::GetWindow()
{
    return window;
}
zEngine::zEngine()
{
    GLLib::GLInit();
    window = GLLib::CreateWindow(WindowX,WindowY);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    InputSystem::GetInstance()->Init(window);

    ScreenProcessingManagerPtr = NewSPtr<ScreenProcessingManager>(WindowX, WindowY);
    
    zEngine::ins = this;

    InitLevel();
}

float convertToSeconds(std::chrono::microseconds microseconds) {
    return static_cast<float>(microseconds.count()) / 1e6f;
}


void zEngine::Run()
{
    constexpr int64 TargetFreamRate = 60;
    constexpr std::chrono::microseconds MinFreamTime =
        std::chrono::microseconds(1000000 / TargetFreamRate);
    Timer t{"MainLoop"};
    while (!glfwWindowShouldClose(window))
    {

        t.Reset();
        processInput(window);
        Camera::GetCamera()->Update(DeltaTime);

        Update();
        
        glClearColor(0,0,0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // MaxFpsControl
        {
            std::chrono::microseconds timeSpan = t.GetTimeSpan();
            while(timeSpan < MinFreamTime)
            {
                timeSpan = t.GetTimeSpan();
            }
            DeltaTime = convertToSeconds(timeSpan);
        }
    }

    glfwTerminate();
}

void zEngine::InitLevel()
{
    // addLevel(DrawSanjiaoxing);
    addLevel(DrawShadow); 
    addLevel(DrawFrameBuffer); 
    addLevel(DrawSkyBox); 
    addLevel(DrawBlend); 
    addLevel(DrawStencilTest);
    addLevel(DrawDepthTestBuffer);
    // addLevel(DrawNanosuit);
    // addLevel(DrawRTSJX);
    // addLevel(DrawBox);
    // addLevel(DrawTexBox);
    // addLevel(DrawBoxWithLight);
    addLevel(DrawTexBoxWithLight);
    addLevel(DrawBoxWithMat);
    addLevel(DrawAdvanceLight);
}

void zEngine::InitInput()
{
    InputSystem::GetInstance()->Init(window);
}

void zEngine::SetLevel(int index)
{
    if(levelList.size() + 1 < index)
    {
        return;
    }
    levelList[index - 1](); 
}

float zEngine::GetDeltaTime()
{
    return DeltaTime;
}

SPtr<ScreenProcessingManager> zEngine::GetScreenProcessingManagerPtr()
{
    return ScreenProcessingManagerPtr;
}

zEngine* zEngine::GetInstance()
{
    return ins;
}

void zEngine::Draw()
{

    

    
    DrawPreProcessing();
    level->Draw();
    RenderCommandQueue::Flush();
    DrawPostProcessing();
}

void zEngine::Update()
{
    GLLib::processECSInput(window);
    level->Update(DeltaTime);
}

void zEngine::DrawPreProcessing()
{
    ScreenProcessingManagerPtr->PreProcessing();
}

void zEngine::DrawPostProcessing()
{
    ScreenProcessingManagerPtr->PostProcessing();
}

