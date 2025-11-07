#pragma once
#include "geometry.h"
#include <string>
#include <vector>

// Model class

// This class represents a 3D model loaded from an .obj file.
// It stores all the vertices and the indices that define each face (triangle).
class Model {
    // List of all vertex positions in the model
    std::vector<vec3> vertexPositions;

    // List of vertex indices that make up each face (3 per triangle)
    std::vector<int> faceVertexIndices;

public:
    // Loads the model from a given .obj file
    Model(const std::string& filename);

    // Returns how many vertices exist in total
    int getVertexCount() const;

    // Returns how many faces (triangles) exist
    int getFaceCount() const;

    // Get a vertex directly by its index
    vec3 getVertex(int index) const;

    // Get a vertex from a specific face and corner 0 = A, 1 = B, 2 = C
    vec3 getVertexFromFace(int faceIndex, int corner) const;
};
