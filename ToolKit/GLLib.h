#pragma once

struct GLFWwindow;

class GLLib
{
public:
    static void GLInit();

    static GLFWwindow* CreateWindow(int width,int height);

    static void processECSInput(GLFWwindow* window);

    static void framebuffer_size_callback
        (GLFWwindow* window, int width, int height);
    void GLADinit();
};