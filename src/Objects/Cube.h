#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <vector>

class Cube {

public:
    Cube();

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

private:
};

#endif