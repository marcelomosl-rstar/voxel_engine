#include "Chunk.h"

// Chunk::Chunk()
//{
//     Cube cube;
//     float cubeSize = 1.0f; // The size of each cube is 1.0 unit
//
//     int gridSize = 240; // 10x10 grid
//
//     for (int row = 0; row < gridSize; ++row) { // Loop through rows
//         for (int col = 0; col < gridSize; ++col) { // Loop through columns
//             float xOffset = col * cubeSize; // Offset along the x-axis
//             float zOffset = row * cubeSize; // Offset along the z-axis
//
//             // Add each cube's vertices with the xOffset and zOffset
//             for (size_t j = 0; j < cube.vertices.size(); j += 3) { // Step by 3 for X, Y, Z
//                 vertices.push_back(cube.vertices[j] + xOffset); // X-coordinate
//                 vertices.push_back(cube.vertices[j + 1]); // Y-coordinate
//                 vertices.push_back(cube.vertices[j + 2] + zOffset); // Z-coordinate
//
//                 // Copy the rest (colors and texcoords)
//                 // vertices.push_back(cube.vertices[j + 3]); // R
//                 // vertices.push_back(cube.vertices[j + 4]); // G
//                 // vertices.push_back(cube.vertices[j + 5]); // B
//                 // vertices.push_back(cube.vertices[j + 6]); // TexCoord U
//                 // vertices.push_back(cube.vertices[j + 7]); // TexCoord V
//             }
//
//             // Add indices with the correct offset
//             unsigned int indexOffset = (row * gridSize + col) * 24; // Each cube has 24 indices
//             for (size_t k = 0; k < cube.indices.size(); ++k) {
//                 indices.push_back(cube.indices[k] + indexOffset);
//             }
//         }
//     }
// }

bool Chunk::isNeighborPresent(int x, int y, int z)
{
    return grid.count({ x, y, z }) > 0;
}

Chunk::Chunk()
{
    Cube cube;
    float cubeSize = 1.0f;
    int gridSize = 10;

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            grid.emplace(GridKey { col, 0, row }); // y = 0
        }
    }

    // Iterate over the grid to create vertices and indices for visible faces
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int x = col;
            int y = 0; // Assuming a flat plane
            int z = row;

            // Check each face and add only if it's not blocked
            if (!isNeighborPresent(x - 1, y, z)) {
                // Add left face
                addFace(cube, x, y, z, LEFT_FACE);
            }
            if (!isNeighborPresent(x + 1, y, z)) {
                // Add right face
                addFace(cube, x, y, z, RIGHT_FACE);
            }
            if (!isNeighborPresent(x, y - 1, z)) {
                // Add bottom face
                addFace(cube, x, y, z, BOTTOM_FACE);
            }
            if (!isNeighborPresent(x, y + 1, z)) {
                // Add top face
                addFace(cube, x, y, z, TOP_FACE);
            }
            if (!isNeighborPresent(x, y, z - 1)) {
                // Add back face
                addFace(cube, x, y, z, BACK_FACE);
            }
            if (!isNeighborPresent(x, y, z + 1)) {
                // Add front face
                addFace(cube, x, y, z, FRONT_FACE);
            }
        }
    }
}

void Chunk::addFace(const Cube& cube, int x, int y, int z, FaceType faceType)
{
    float cubeSize = 1.0f;

    // Base vertex position for the cube's corner at (x, y, z)
    float baseX = x * cubeSize;
    float baseY = y * cubeSize;
    float baseZ = z * cubeSize;

    // Vertices for each face (assuming counter-clockwise winding order)
    std::vector<float> faceVertices;
    switch (faceType) {
    case FRONT_FACE:
        // Front face (z = baseZ + cubeSize)
        faceVertices = {
            baseX, baseY, baseZ + cubeSize,
            baseX + cubeSize, baseY, baseZ + cubeSize,
            baseX + cubeSize, baseY + cubeSize, baseZ + cubeSize,
            baseX, baseY + cubeSize, baseZ + cubeSize
        };
        break;
    case BACK_FACE:
        // Back face (z = baseZ)
        faceVertices = {
            baseX, baseY, baseZ,
            baseX + cubeSize, baseY, baseZ,
            baseX + cubeSize, baseY + cubeSize, baseZ,
            baseX, baseY + cubeSize, baseZ
        };
        break;
    case LEFT_FACE:
        // Left face (x = baseX)
        faceVertices = {
            baseX, baseY, baseZ,
            baseX, baseY, baseZ + cubeSize,
            baseX, baseY + cubeSize, baseZ + cubeSize,
            baseX, baseY + cubeSize, baseZ
        };
        break;
    case RIGHT_FACE:
        // Right face (x = baseX + cubeSize)
        faceVertices = {
            baseX + cubeSize, baseY, baseZ,
            baseX + cubeSize, baseY, baseZ + cubeSize,
            baseX + cubeSize, baseY + cubeSize, baseZ + cubeSize,
            baseX + cubeSize, baseY + cubeSize, baseZ
        };
        break;
    case TOP_FACE:
        // Top face (y = baseY + cubeSize)
        faceVertices = {
            baseX, baseY + cubeSize, baseZ,
            baseX + cubeSize, baseY + cubeSize, baseZ,
            baseX + cubeSize, baseY + cubeSize, baseZ + cubeSize,
            baseX, baseY + cubeSize, baseZ + cubeSize
        };
        break;
    case BOTTOM_FACE:
        // Bottom face (y = baseY)
        faceVertices = {
            baseX, baseY, baseZ,
            baseX + cubeSize, baseY, baseZ,
            baseX + cubeSize, baseY, baseZ + cubeSize,
            baseX, baseY, baseZ + cubeSize
        };
        break;
    }

    // Add face vertices to the chunk's vertices
    vertices.insert(vertices.end(), faceVertices.begin(), faceVertices.end());

    // Indices for the two triangles making up the face
    unsigned int baseIndex = static_cast<unsigned int>(vertices.size() / 3 - 4);
    std::vector<unsigned int> faceIndices = {
        baseIndex, baseIndex + 1, baseIndex + 2, // First triangle
        baseIndex, baseIndex + 2, baseIndex + 3 // Second triangle
    };

    // Add face indices to the chunk's indices
    indices.insert(indices.end(), faceIndices.begin(), faceIndices.end());
}
