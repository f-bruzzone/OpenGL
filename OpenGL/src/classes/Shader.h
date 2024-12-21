#pragma once
#include <string>

struct ShaderProgram
{
    std::string Vertex;
    std::string Fragment;
};

class Shader
{
public:
    Shader(const char* filepath);

    void Bind() const;
    int GetUniformLocation(const char* name) const;

private:
    unsigned int m_ProgramId;

    ShaderProgram ParseShader(const char* filepath);
    void LoadShader(const char* vertex, const char* fragment);
};