#pragma once

class Texture
{
public:
    Texture(const char* filepath);
    ~Texture();

    void Bind(unsigned int texSlot) const;

private:
    unsigned int m_TextureId;
    unsigned int LoadImage(const char* filepath);
};