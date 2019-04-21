#pragma once

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

		int runTest();

	private:
		int initializeGLFWWindow();

		std::unique_ptr<OpenGlEngine> mEngine;

		GLFWwindow* mWindow;
	};

}
}