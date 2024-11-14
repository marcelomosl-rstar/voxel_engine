#include "Cube.h"

Cube::Cube()
{
    indices = {
        0, 1, 2, // First triangle of the front face
        2, 3, 0, // Second triangle of the front face
        4, 5, 6, // First triangle of the back face
        6, 7, 4, // Second triangle of the back face
        0, 1, 5, // First triangle of the left face
        5, 4, 0, // Second triangle of the left face
        2, 3, 7, // First triangle of the right face
        7, 6, 2, // Second triangle of the right face
        0, 3, 7, // First triangle of the top face
        7, 4, 0, // Second triangle of the top face
        1, 2, 6, // First triangle of the bottom face
        6, 5, 1 // Second triangle of the bottom face
    };

    vertices = {
        //     COORDINATES            /        COLORS            /   TexCoord  //
        -0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Vertex 0
        0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Vertex 1
        0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Vertex 2
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Vertex 3
        -0.5f, 0.5f, 0.5f, 0.92f, 0.86f, 0.76f, 0.0f, 0.0f, // Vertex 4
        0.5f, 0.5f, 0.5f, 0.92f, 0.86f, 0.76f, 1.0f, 0.0f, // Vertex 5
        0.5f, 0.5f, -0.5f, 0.92f, 0.86f, 0.76f, 1.0f, 1.0f, // Vertex 6
        -0.5f, 0.5f, -0.5f, 0.92f, 0.86f, 0.76f, 0.0f, 1.0f // Vertex 7
    };
}
