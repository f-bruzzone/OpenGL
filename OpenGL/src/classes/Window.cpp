#include "Window.h"
#include "GLFW/glfw3.h"

#include <iostream>

Window::Window()
{
    GLFWwindow* window = m_Window;
    Init();
}

Window::~Window()
{
}

void Window::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        std::cerr << "Error initializing library" << std::endl;

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(960, 720, "Hello World", NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        std::cerr << "Error initializing window" << std::endl;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
}
