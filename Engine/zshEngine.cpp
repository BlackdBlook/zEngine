#include "zshEngine.h"
#include "../ToolKit/GLLib.h"
#include "../Levels/DrawSJX/DrawSanjiaoxing.h"
#include "../Levels/DrawRTSJX/DrawRTSJX.h"
#include "../Levels/DrawBox/DrawBox.h"
#include "../Levels/DrawTexBox/DrawTexBox.h"
#include <GLFW/glfw3.h>

#define makeLevel(s) \
level = std::shared_ptr<s>(new s());\
level->Init();

#define LEVEL_COUNT 4


void zshEngine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    for (int i = GLFW_KEY_0; i <= GLFW_KEY_0 + LEVEL_COUNT; i++)
    {
        if (glfwGetKey(window, i) == GLFW_PRESS)
        {
            SetLevel(i - GLFW_KEY_0);
        }
    }
}
zshEngine::zshEngine()
{
    GLLib::GLInit();
    window = GLLib::CreateWindow(1280,720);
    glEnable(GL_DEPTH_TEST);

}

void zshEngine::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        Camera::GetCamera()->Update();
        Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void zshEngine::SetLevel(int index)
{
    switch (index)
    {
    case 0:
        makeLevel(DrawSanjiaoxing);
        break;
    case 1: 
        makeLevel(DrawRTSJX);
        break;
    case 2: 
        makeLevel(DrawBox);
        break;
    case 3:
        makeLevel(DrawTexBox);
        break;
    default:
        break;
    }
}

void zshEngine::Draw()
{
    level->Draw();
}

void zshEngine::Update()
{
    GLLib::processECSInput(window);
    level->Update();
}

