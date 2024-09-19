#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO {
public:
	EBO(GLuint* indices, GLsizeiptr size);
	GLuint ID;


	void Bind();
	void Unbind();
	void Delete();
};

#endif