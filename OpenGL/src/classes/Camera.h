#pragma once
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include "../vendor/glm/gtx/vector_angle.hpp"

class GLFWwindow;
class Window;

class Camera
{
private:
    std::shared_ptr<Window> m_Window;
    int m_WindowWidth;
    int m_WindowHeight;
    glm::vec3 m_CurPos;
    float m_HorizontalAngle;
    float m_VerticalAngle;
    float m_MouseSpeed;
    float m_MoveSpeed;
    glm::vec3 m_LookDir;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    bool b_InitialCurPlacement;

    glm::mat4 m_View;
    glm::mat4 m_Perspective;

public:
    Camera(std::shared_ptr<Window> window);
    ~Camera();

    void GetInput();
    void UpdateCamera();
    inline glm::mat4 GetPerspectiveMat() { return m_Perspective; }
    inline glm::mat4 GetViewMat() { return m_View; };
    inline glm::vec3 GetPosition() { return m_CurPos; }
    inline glm::vec3 GetLookDirection() { return m_LookDir; }

private:
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    void HandleCursorPosition(double xpos, double ypos);
    void UpdateLookDirection();
    void UpdateRightVector();
    void UpdateUpVector();
    void UpdateViewMat();
};