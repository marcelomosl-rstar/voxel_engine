#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <cerrno>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

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