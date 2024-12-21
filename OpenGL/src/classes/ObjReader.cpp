#include "ObjReader.h"
#include <fstream>
#include <string>

ObjReader::ObjReader()
    : m_Normals{ 0 }, m_TexCoords{ 0 }, m_Vertices{ 0 }
{}

void ObjReader::ParseObject(const char* filepath, std::vector<float>&vertices)
{
    ReadFile(filepath);
    PopulateVertices(vertices);
    ResetReader();
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
