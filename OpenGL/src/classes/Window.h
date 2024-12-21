#pragma once
#include "GLFW/glfw3.h"

class GLFWwindow;

class Window
{
private:
    GLFWwindow* m_Window;

public:
    Window();
    ~Window();

    inline GLFWwindow* GetWindow() { return m_Window; }
    inline void Terminate() { glfwTerminate(); }
    inline bool WindowShouldClose() { return glfwWindowShouldClose(m_Window); }
    inline void CloseWindow() { glfwSetWindowShouldClose(m_Window, 1); }

private:
    void Init();
};
