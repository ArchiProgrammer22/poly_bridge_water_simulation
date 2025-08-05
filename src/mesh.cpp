#include "mesh.h"
#include <iostream>
#include <random>

Mesh::Mesh(float width, float depth, int numSegmentsX, int numSegmentsZ) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    float segmentWidth = width / numSegmentsX;
    float segmentDepth = depth / numSegmentsZ;
    float displacementScale = 0.5f;

    for (int z = 0; z <= numSegmentsZ; ++z) {
        for (int x = 0; x <= numSegmentsX; ++x) {
            Vertex v;

            float xPos = x * segmentWidth;
            float zPos = z * segmentDepth;

            float offsetX = dist(rng) * segmentWidth * displacementScale;
            float offsetZ = dist(rng) * segmentDepth * displacementScale;

            v.Position = glm::vec3(xPos + offsetX, 0.0f, zPos + offsetZ);
            vertices.push_back(v);
        }
    }

    int numVerticesX = numSegmentsX + 1;
    for (int z = 0; z < numSegmentsZ; ++z) {
        for (int x = 0; x < numSegmentsX; ++x) {
            unsigned int bottomLeft = z * numVerticesX + x;
            unsigned int bottomRight = z * numVerticesX + x + 1;
            unsigned int topLeft = (z + 1) * numVerticesX + x;
            unsigned int topRight = (z + 1) * numVerticesX + x + 1;

            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(bottomRight);

            indices.push_back(topLeft);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
        }
    }
    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glBindVertexArray(0);
}

void Mesh::Draw() {
    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
