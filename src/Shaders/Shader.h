#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <stdexcept>
#include <filesystem>



std::string GetFile(const char* fileName);

class Shader {
public:
	GLuint ID;


	Shader(const char* VertexFile, const char* FragmentFile);

	void Activate();
	void Delete();

private:
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif