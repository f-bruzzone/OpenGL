#include "Shader.h"
#include "GL/glew.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* filepath)
{
    ShaderProgram shaderProgram = ParseShader(filepath);
    LoadShader(shaderProgram.Vertex.c_str(), shaderProgram.Fragment.c_str());
}

void Shader::Bind() const
{
    glUseProgram(m_ProgramId);
}

int Shader::GetUniformLocation(const char* name) const
{
    return glGetUniformLocation(m_ProgramId, name);
}

ShaderProgram Shader::ParseShader(const char* file)
{
    std::ifstream stream(file);
    std::string line;
    std::stringstream ss[2];

    enum ProgramType
    {
        Vertex = 0,
        Fragment = 1
    };

    ProgramType type;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ProgramType::Vertex;
            else if (line.find("fragment") != std::string::npos)
                type = ProgramType::Fragment;
        }
        else
        {
            ss[type] << line << "\n";
        }
    }

    return { ss[ProgramType::Vertex].str(), ss[ProgramType::Fragment].str() };
}

void Shader::LoadShader(const char* vertex, const char* fragment)
{
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertex, nullptr);
    glCompileShader(vShader);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragment, nullptr);
    glCompileShader(fShader);

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vShader);
    glAttachShader(m_ProgramId, fShader);
    glLinkProgram(m_ProgramId);

    // check if shader compiles
    GLint success;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint logLength = 0;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 1)
        {
            //char* log = new char[logLength];
            char* log = (char*)alloca(sizeof(char) * logLength);
            glGetProgramInfoLog(m_ProgramId, logLength, NULL, log);
            std::cerr << "Shader program linking failed: " << log << std::endl;
        }
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}
