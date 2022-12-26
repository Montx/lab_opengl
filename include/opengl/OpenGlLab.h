#pragma once

#include "GLMHeaders.h"

#include <memory>

struct GLFWwindow;

namespace lab {
namespace opengl {

	class OpenGlEngine;
	class Camera;

	class OpenGlLab {
	public:
		~OpenGlLab();

		OpenGlLab();

		int initialize();

		int runTest1();
		int runTest2();
		int runTest3();

	private:
		int initializeGLFWWindow();

		void processInput(GLFWwindow *window);

		std::unique_ptr<OpenGlEngine> mEngine;

		GLFWwindow* mWindow;
	};

}
}