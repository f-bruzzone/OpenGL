#pragma once
#include <vector>
#include "../vendor/glm/gtc/matrix_transform.hpp"

class ObjReader
{
public:
    ObjReader();
    ~ObjReader() = default;

    void ParseObject(const char* filepath, std::vector<float>& vertices);
    void BuildObjectTangents(const std::vector<float>& vertices, const unsigned int vertexValLen, std::vector<glm::vec3>& allTangents);

private:
    std::vector<glm::vec3> m_Vertices;
    std::vector<glm::vec3> m_Normals;
    std::vector<glm::vec2> m_TexCoords;
    std::vector<unsigned int> m_Indices;

    void ReadFile(const char* filepath);
    void PopulateVertices(std::vector<float>& vertices);
    void ResetReader();
};