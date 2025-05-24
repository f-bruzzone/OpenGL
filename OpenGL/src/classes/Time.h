#pragma once
#include "GLFW/glfw3.h"

class Time
{
public:
    Time() = delete;

    inline static float DeltaTime() { return m_DeltaTime; }
    static void UpdateTime();

private:
    static float m_LastTime;
    static float m_DeltaTime;
    static float m_CurrentTime;
    static float m_LastFPSTime;
    static unsigned int m_nbFrames;

    static void FPSCounter();
};