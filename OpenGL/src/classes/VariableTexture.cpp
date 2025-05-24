#include "../vendor/stb_image.h"
#include "VariableTexture.h"
#include "GL/glew.h"

#include <iostream>

VariableTexture::VariableTexture(const char* filepath, TextureType type)
{
    switch (type)
    {
    case TextureType::Trilinear:
        m_TextureId = LoadImage(filepath);
        break;

    case TextureType::Nearest:
        m_TextureId = LoadImage2(filepath);
        break;

    case TextureType::Linear:
        m_TextureId = LoadImage3(filepath);
        break;

    case TextureType::Anisotropic:
        m_TextureId = LoadImage4(filepath);
        break;

    case TextureType::CubeMap:
        m_TextureId = LoadCubeMap(filepath);
        break;
    }
}

VariableTexture::~VariableTexture()
{
}

void VariableTexture::Bind(unsigned int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void VariableTexture::BindCubeMap(unsigned int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);
}

unsigned int VariableTexture::LoadImage(const char* filepath)
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

    int format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    if (!glIsTexture(texId))
        std::cerr << "Failed to load VariableTexture : " << texId << "\n";

    return texId;
}

unsigned int VariableTexture::LoadImage2(const char* filepath)
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //float maxAniso;
    //glGetFloatv(GL_MAX_VariableTexture_MAX_ANISOTROPY_EXT, &maxAniso);  // Query maximum anisotropy supported
    //glTexParameteri(GL_VariableTexture_2D, GL_VariableTexture_MAX_ANISOTROPY_EXT, maxAniso);

    int format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    if (!glIsTexture(texId))
        std::cerr << "Failed to load VariableTexture : " << texId << "\n";

    return texId;
}

unsigned int VariableTexture::LoadImage3(const char* filepath)
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //float maxAniso;
    //glGetFloatv(GL_MAX_VariableTexture_MAX_ANISOTROPY_EXT, &maxAniso);  // Query maximum anisotropy supported
    //glTexParameteri(GL_VariableTexture_2D, GL_VariableTexture_MAX_ANISOTROPY_EXT, maxAniso);

    int format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    if (!glIsTexture(texId))
        std::cerr << "Failed to load VariableTexture : " << texId << "\n";

    return texId;
}

unsigned int VariableTexture::LoadImage4(const char* filepath)
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

    float maxAniso;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);  // Query maximum anisotropy supported
    std::cout << "max anisotropy " << maxAniso << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);

    int format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    if (!glIsTexture(texId))
        std::cerr << "Failed to load VariableTexture : " << texId << "\n";

    return texId;
}

unsigned int VariableTexture::LoadCubeMap(const char* filepath)
{
    std::string dirName = filepath;
    std::string names[] = {
        "/right.jpg",
        "/left.jpg",
        "/top.jpg",
        "/bottom.jpg",
        "/front.jpg",
        "/back.jpg",
    };

    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    int width, height, channels;
    unsigned char* data;
    for (size_t i = 0; i < 6; i++)
    {
        data = stbi_load((dirName + names[i]).c_str(), &width, &height, &channels, 0);
        if (data == nullptr)
        {
            std::cerr << "Failed to load image\n";
            return 0;
        }

        int format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);

        if (!glIsTexture(texId))
            std::cerr << "Failed to load CubeMap texture: " << texId << "\n";

    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texId;
}