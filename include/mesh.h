#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
};

class Mesh {
public:
    Mesh(float width, float depth, int numSegmentsX, int numSegmentsZ);

    void Draw();

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;
};
