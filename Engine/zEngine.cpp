#include "zEngine.h"
#include "../ToolKit/GLLib.h"
#include "../Levels/DrawSJX/DrawSanjiaoxing.h"
#include "../Levels/DrawRTSJX/DrawRTSJX.h"
#include "../Levels/DrawBox/DrawBox.h"
#include "../Levels/DrawTexBox/DrawTexBox.h"
#include "../Levels/BoxWithLight/DrawBoxWithLight.h"
#include <GLFW/glfw3.h>

#include "../Levels/TexBoxWithLight/DrawTexBoxWithLight.h"
#include "Levels/BoxWithMat/DrawBoxWithMat.h"
#include "Levels/DrawAdvanceLight/DrawAdvanceLight.h"
#include "SubSystem/AssetSystem.h"

#define makeLevel(s) \
level = std::shared_ptr<s>(new s());\
level->Init();\
level->Start()

#define addLevel(s) \
levelList.emplace_back([this]() \
{                               \
    makeLevel(s);               \
})                              

#define LEVEL_COUNT 6

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
    
    for (int i = GLFW_KEY_0; i < GLFW_KEY_0 + levelList.size(); i++)
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
    window = GLLib::CreateWindow(1280,720);
    glEnable(GL_DEPTH_TEST);

    AssetSystem::GetInstance();
    
    InitLevel();

    zEngine::ins = this;
}

void zEngine::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        Camera::GetCamera()->Update();
        Update();
        glClearColor(0,0,0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void zEngine::InitLevel()
{
    addLevel(DrawSanjiaoxing);
    addLevel(DrawRTSJX);
    addLevel(DrawBox);
    addLevel(DrawTexBox);
    addLevel(DrawBoxWithLight);
    addLevel(DrawTexBoxWithLight);
    addLevel(DrawBoxWithMat);
    addLevel(DrawAdvanceLight);
}

void zEngine::SetLevel(int index)
{
    levelList[index]();
}

zEngine* zEngine::GetInstance()
{
    return ins;
}

void zEngine::Draw()
{
    level->Draw();
}

void zEngine::Update()
{
    GLLib::processECSInput(window);
    level->Update();
}

