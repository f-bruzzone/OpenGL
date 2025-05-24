#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"
#include "Texture.h"
#include "GL/glew.h"

#include <iostream>

Texture::Texture(const char* filepath)
{
    m_TextureId = LoadImage(filepath);
}

Texture::~Texture()
{
}

void Texture::Bind(unsigned int texSlot) const
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

unsigned int Texture::LoadImage(const char* filepath)
{
    int width, height, channels;

    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);
    if (data == nullptr)
    {
        std::cerr << "Failed to load image\n";
        return 0;
    }

    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //float maxAniso;
    //glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);  // Query maximum anisotropy supported
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);

    int format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    if (!glIsTexture(texId))
        std::cerr << "Failed to load texture : " << texId << "\n";

    return texId;
}
