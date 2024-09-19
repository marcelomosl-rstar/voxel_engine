#include "Shader.h"

std::string GetFile(const char* fileName) {
	std::ifstream in(fileName, std::ios::binary);

	if (!in.is_open()) {
		std::cerr << "Failed to open file: " << fileName << std::endl;
		std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
		throw std::runtime_error("Failed to open file");
	}

	std::stringstream contents;
	contents << in.rdbuf();
	return contents.str();
}

Shader::Shader(const char* VertexFile, const char* FragmentFile) {
	std::string vertexCode = GetFile(VertexFile);
	std::string fragmentCode = GetFile(FragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Compile Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	// Compile Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// Link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
