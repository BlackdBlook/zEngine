#pragma once
#include "Typedef.h"

struct GLFWwindow;

class GLLib
{
public:
    static void GLInit();

    static GLFWwindow* CreateWindow(int width,int height);

    static void processECSInput(GLFWwindow* window);

    static void framebuffer_size_callback
        (GLFWwindow* window, int width, int height);

    // 获取最大纹理单元数量
    static int GetMaxTextureUnitCount();
    
    void GLADinit();
};