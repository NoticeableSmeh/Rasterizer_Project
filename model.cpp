#include "model.h"
#include <fstream>
#include <sstream>

using namespace std;

// Small helper function to check if a line starts with a certain leter etc etc
bool starts_with_which_letter(const string& str, const string& firstLetter)
{
    return str.size() >= firstLetter.size() && str.compare(0, firstLetter.size(), firstLetter) == 0;
}

// This function reads a .obj file and stores all the vertex positions
// and face indices so we can later draw them.
Model::Model(const string& filename)
{
    ifstream modelInput(filename);
    if (!modelInput)
        throw runtime_error("cannot open: " + filename);

    string currentLine;

    while (getline(modelInput, currentLine)) {
        if (currentLine.empty())
            continue;

        // Lines starting with "v " define points
        if (starts_with_which_letter(currentLine, "v ")) {
            istringstream iss(currentLine.substr(2));
            double x, y, z;

            // Read the three coordinates and add to vertex list
            if (iss >> x >> y >> z)
                vertexPositions.emplace_back(x, y, z);
            continue;
        }

        // Lines starting with "f " define faces
        if (starts_with_which_letter(currentLine, "f ")) {
            istringstream iss(currentLine.substr(2));
            string section;

            // Each face line contains three or more vertex references
            // formatted: "f 1/1/1 2/2/2 3/3/3"
            while (iss >> section) {
                int slashPos = section.find('/');

                // Extract the vertex index before the first '/
                int index = stoi(section.substr(0, slashPos));

                // Store the index
                faceVertexIndices.push_back(index - 1);
            }
            continue;
        }
    }
}

// Returns the total number of vertices in the model
int Model::getVertexCount() const
{
    return static_cast<int>(vertexPositions.size());
}

// Returns the total number of faces (triangles)
int Model::getFaceCount() const
{
    return static_cast<int>(faceVertexIndices.size() / 3);
}

// Returns the vertex at a specific index
vec3 Model::getVertex(int index) const
{
    return vertexPositions[index];
}

// Returns the vertex at a given corner of a specific face
// faceIndex = which triangle, corner = 0 (A), 1 (B), or 2 (C)
vec3 Model::getVertexFromFace(int faceIndex, int corner) const
{
    int index = faceVertexIndices[faceIndex * 3 + corner];
    return vertexPositions[index];
}
