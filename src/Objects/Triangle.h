#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <vector>



class Triangle {

public:
	Triangle();

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
private:

};


#endif