#pragma once

enum TextureType
{
    Linear = 1,
    Nearest = 2,
    Trilinear = 3,
    CubeMap = 4,
    Anisotropic = 5
};

class VariableTexture
{
public:
    VariableTexture(const char* filepath, TextureType type);
    ~VariableTexture();

    void Bind(unsigned int texSlot);
    void BindCubeMap(unsigned int texSlot);

private:
    unsigned int m_TextureId;
    unsigned int LoadImage(const char* filepath);
    unsigned int LoadImage2(const char* filepath);
    unsigned int LoadImage3(const char* filepath);
    unsigned int LoadImage4(const char* filepath);
    unsigned int LoadCubeMap(const char* filepath);
};