#include "Chunk.h"

Chunk::Chunk()
{
    Cube cube;
    float cubeSize = 1.0f; // the size of each cube is 1.0 unit

    for (int i = 0; i < 10; ++i) { // Create cubes side by side
        float xOffset = i * cubeSize; // Offset along the x-axis

        // Add each cube's vertices with the xOffset
        for (size_t j = 0; j < cube.vertices.size(); j += 3) { // Step by 8 (3 coords + 3 color + 2 texcoords)
            vertices.push_back(cube.vertices[j] + xOffset); // X-coordinate
            vertices.push_back(cube.vertices[j + 1]); // Y-coordinate
            vertices.push_back(cube.vertices[j + 2]); // Z-coordinate

            // Copy the rest (colors and texcoords)
            // vertices.push_back(cube.vertices[j + 3]); // R
            // vertices.push_back(cube.vertices[j + 4]); // G
            // vertices.push_back(cube.vertices[j + 5]); // B
            // vertices.push_back(cube.vertices[j + 6]); // TexCoord U
            // vertices.push_back(cube.vertices[j + 7]); // TexCoord V
        }

        // Add indices with the correct offset
        unsigned int indexOffset = i * 24; // Each cube has 24 indices (6 faces * 2 triangles per face * 3 vertices per triangle)
        for (size_t k = 0; k < cube.indices.size(); ++k) {
            indices.push_back(cube.indices[k] + indexOffset);
        }
    }
}
