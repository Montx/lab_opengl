#pragma once

#include "GLMHeaders.h"

#include <memory>

struct GLFWwindow;

namespace lab {
namespace opengl {

	class OpenGlEngine;

	class OpenGlLab {
	public:
		~OpenGlLab();

		OpenGlLab();

		int initialize();

		int runTest1();
		int runTest2();

	private:
		int initializeGLFWWindow();
		void processInput(GLFWwindow *window);

		std::unique_ptr<OpenGlEngine> mEngine;

		GLFWwindow* mWindow;
		glm::vec3 mCameraPos;
		glm::vec3 mCameraFront;
		glm::vec3 mCameraUp;
	};

}
}