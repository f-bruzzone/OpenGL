#include "Time.h"
#include <iostream>

float Time::m_LastTime = 0.0f;
float Time::m_DeltaTime = 0.0f;
float Time::m_CurrentTime = 0.0f;
float Time::m_LastFPSTime = glfwGetTime();
unsigned int Time::m_nbFrames = 0;

void Time::UpdateTime()
{
    m_CurrentTime = static_cast<float>(glfwGetTime());
    m_DeltaTime = m_CurrentTime - m_LastTime;
    m_LastTime = m_CurrentTime;

    FPSCounter();
}

void Time::FPSCounter()
{
    m_nbFrames++;

    if (m_CurrentTime - m_LastFPSTime > 1.0f)
    {
        //std::cout << "ms/frame: " << 1000 / double(m_nbFrames) << std::endl;
        m_nbFrames = 0;
        m_LastFPSTime += 1.0f;
    }
}
