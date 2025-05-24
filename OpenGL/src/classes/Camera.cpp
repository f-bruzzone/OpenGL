#include "Camera.h"
#include "Window.h"
#include "Time.h"


Camera::Camera(std::shared_ptr<Window> window)
    : m_Window{ window }, m_CurPos{ 0, 0, -3 }, m_HorizontalAngle{ 0 }, m_VerticalAngle{ 0 },
    m_MouseSpeed{ 0.25f }, m_MoveSpeed{ 2.5f }, m_LookDir{ 0 }, m_Right{ 0 }, m_Up{ 0, 1, 0 },
    m_Perspective{ glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.01f, 100.0f) },
    m_View{ glm::lookAt(m_CurPos, glm::vec3(0), m_Up) }, b_InitialCurPlacement{ true }
{
    glfwSetCursorPosCallback(m_Window->GetWindow(), Camera::cursor_position_callback);
    glfwGetWindowSize(m_Window->GetWindow(), &m_WindowWidth, &m_WindowHeight);
    glfwSetWindowUserPointer(m_Window->GetWindow(), this);
}

Camera::~Camera()
{
}

void Camera::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera)
        camera->HandleCursorPosition(xpos, ypos);
}

void Camera::HandleCursorPosition(double xpos, double ypos)
{
    if (b_InitialCurPlacement)
    {
        xpos = m_WindowWidth / 2;
        ypos = m_WindowHeight / 2;
        b_InitialCurPlacement = false;
    }
    glfwSetCursorPos(m_Window->GetWindow(), (m_WindowWidth / 2), (m_WindowHeight / 2));

    m_HorizontalAngle += m_MouseSpeed * Time::DeltaTime() * (m_WindowWidth / 2 - xpos);
    m_VerticalAngle += m_MouseSpeed * Time::DeltaTime() * (m_WindowHeight / 2 - ypos);
    m_VerticalAngle = std::max(-3.0f, std::min(m_VerticalAngle, 3.0f));
}

void Camera::GetInput()
{
    // Move forward
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        m_CurPos += m_LookDir * Time::DeltaTime() * m_MoveSpeed;
    }
    // Move backward
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        m_CurPos -= m_LookDir * Time::DeltaTime() * m_MoveSpeed;
    }
    // Strafe right
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        m_CurPos += m_Right * Time::DeltaTime() * m_MoveSpeed;
    }
    // Strafe left
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        m_CurPos -= m_Right * Time::DeltaTime() * m_MoveSpeed;
    }
    // Move down
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_CurPos -= m_Up * Time::DeltaTime() * m_MoveSpeed;
    }
    // Move up
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        m_CurPos += m_Up * Time::DeltaTime() * m_MoveSpeed;
    }
    // Quit
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_Window->CloseWindow();
    }
}

void Camera::UpdateLookDirection()
{
    m_LookDir = glm::vec3(
        glm::cos(m_VerticalAngle) * sin(m_HorizontalAngle),
        glm::sin(m_VerticalAngle),
        glm::cos(m_VerticalAngle) * cos(m_HorizontalAngle)
    );
}

void Camera::UpdateRightVector()
{
    m_Right = glm::vec3(
        glm::sin(m_HorizontalAngle - 3.14f / 2.0f),
        0,
        glm::cos(m_HorizontalAngle - 3.14f / 2.0f)
    );
}

void Camera::UpdateUpVector()
{
    m_Up = glm::cross(m_Right, m_LookDir);
}

void Camera::UpdateCamera()
{
    GetInput();
    UpdateLookDirection();
    UpdateRightVector();
    UpdateUpVector();
    UpdateViewMat();
}

void Camera::UpdateViewMat()
{
    m_View = glm::lookAt(
        m_CurPos,
        m_CurPos + m_LookDir,
        m_Up
    );
}
