#include "ObjReader.h"
#include <fstream>
#include <string>
#include "../vendor/glm/vec3.hpp"
#include "../vendor/glm/vec2.hpp"

ObjReader::ObjReader()
    : m_Normals{ 0 }, m_TexCoords{ 0 }, m_Vertices{ 0 }
{}

void ObjReader::ParseObject(const char* filepath, std::vector<float>&vertices)
{
    ReadFile(filepath);
    PopulateVertices(vertices);
    ResetReader();
}

void ObjReader::BuildObjectTangents(const std::vector<float> &vertices, const unsigned int vertexValLen, std::vector<glm::vec3>& allTangents)
{
    for (size_t i = 0; i < vertices.size(); i += vertexValLen * 3)
    {
        glm::vec3 p0 = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 p1 = glm::vec3(vertices[i + vertexValLen], vertices[i + vertexValLen + 1], vertices[i + vertexValLen + 2]);
        glm::vec3 p2 = glm::vec3(vertices[i + vertexValLen * 2], vertices[i + vertexValLen * 2 + 1], vertices[i + vertexValLen * 2 + 2]);

        glm::vec2 uv0 = glm::vec2(vertices[i + 3], vertices[i + 4]);
        glm::vec2 uv1 = glm::vec2(vertices[i + vertexValLen + 3], vertices[i + vertexValLen + 4]);
        glm::vec2 uv2 = glm::vec2(vertices[i + vertexValLen * 2 + 3], vertices[i + vertexValLen * 2 + 4]);

        glm::vec3 deltaP1 = p1 - p0;
        glm::vec3 deltaP2 = p2 - p0;

        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaP1 * deltaUV2.y - deltaP2 * deltaUV1.y) * r;
        glm::vec3 biTangent = (deltaP2 * deltaUV1.x - deltaP1 * deltaUV2.x) * r;

        glm::vec3 tanArr[3] = { tangent, tangent, tangent };
        glm::vec3 biTanArr[3] = { biTangent, biTangent, biTangent };

        allTangents.insert(allTangents.end(), std::make_move_iterator(std::begin(tanArr)), std::make_move_iterator(std::end(tanArr)));
        allTangents.insert(allTangents.end(), std::make_move_iterator(std::begin(biTanArr)), std::make_move_iterator(std::end(biTanArr)));
    }
}

void ObjReader::ReadFile(const char* filepath)
{
    std::fstream stream(filepath);
    std::string line;

    while (getline(stream, line))
    {
        std::string header;
        char junkChar;

        stream >> header;

        if (header == "v")
        {
            glm::vec3 vector;
            stream >> vector.x >> std::ws >> vector.y >> std::ws >> vector.z;
            m_Vertices.push_back(vector);
        }
        else if (header == "vt")
        {
            glm::vec2 texCoord;
            stream >> texCoord.x >> std::ws >> texCoord.y;
            m_TexCoords.push_back(texCoord);
        }
        else if (header == "vn")
        {
            glm::vec3 normal;
            stream >> normal.x >> std::ws >> normal.y >> std::ws >> normal.z;
            m_Normals.push_back(normal);
        }
        else if (header == "f")
        {
            unsigned int face[9];

            stream >> face[0] >> junkChar >> face[1] >> junkChar >> face[2] >>
                std::ws >> face[3] >> junkChar >> face[4] >> junkChar >> face[5] >>
                std::ws >> face[6] >> junkChar >> face[7] >> junkChar >> face[8];

            m_Indices.insert(m_Indices.end(), face, face + 9);
        }
    }
}

void ObjReader::PopulateVertices(std::vector<float>& vertices)
{
    for (size_t i = 0; i < m_Indices.size(); i += 3)
    {
        unsigned int index = m_Indices[i] - 1;

        vertices.push_back(m_Vertices[index].x);
        vertices.push_back(m_Vertices[index].y);
        vertices.push_back(m_Vertices[index].z);

        index = m_Indices[i + 1] - 1;

        vertices.push_back(m_TexCoords[index].x);
        vertices.push_back(m_TexCoords[index].y);

        index = m_Indices[i + 2] - 1;

        vertices.push_back(m_Normals[index].x);
        vertices.push_back(m_Normals[index].y);
        vertices.push_back(m_Normals[index].z);
    }
}

void ObjReader::ResetReader()
{
    m_Vertices.clear();
    m_TexCoords.clear();
    m_Normals.clear();
    m_Indices.clear();
}
