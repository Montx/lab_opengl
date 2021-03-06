#pragma once

#include "GLMHeaders.h"

#include <string>

namespace lab {
namespace opengl {

class Shader {
public:
	unsigned int mProgramID;

	// Constructor generates the shader on the fly
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix(const std::string& name, const glm::mat4& matrix);
};

}
}