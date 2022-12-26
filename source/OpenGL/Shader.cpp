#include "Shader.h"

#include <GL/glew.h>

#include "GLMHeaders.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace lab {
namespace opengl {

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// Retrive the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// Read file's buffer contents into streams
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// Compile Shaders
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();

	GLuint sVertexHandler, sFragmentHandler;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	sVertexHandler = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertexHandler, 1, &vShaderCode, NULL);
	glCompileShader(sVertexHandler);

	// Print compile errors if any
	glGetShaderiv(sVertexHandler, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(sVertexHandler, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	sFragmentHandler = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragmentHandler, 1, &fShaderCode, NULL);
	glCompileShader(sFragmentHandler);

	// Print compile errors if any
	glGetShaderiv(sFragmentHandler, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(sFragmentHandler, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Shader Program
	mProgramID = glCreateProgram();
	glAttachShader(mProgramID, sVertexHandler);
	glAttachShader(mProgramID, sFragmentHandler);
	glLinkProgram(mProgramID);

	//Print linking erros if any
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(sVertexHandler);
	glDeleteShader(sFragmentHandler);
}

void Shader::use() {
	glUseProgram(mProgramID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(mProgramID, name.c_str()), value);
}

void Shader::setMatrix(const std::string& name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

}
}