#include "OpenGlLab.h"

#include "OpenGLEngine.h"
#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace lab {
namespace opengl {

	const int k_width = 800;
	const int k_height = 600;

	OpenGlLab::~OpenGlLab() = default;

	OpenGlLab::OpenGlLab() 
		: mEngine(new OpenGlEngine())
		, mWindow(nullptr) {}

	int OpenGlLab::initialize() {
		return initializeGLFWWindow();
	}

	int OpenGlLab::initializeGLFWWindow() {
		glfwInit();

		// Window Properties
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Declaring window
		mWindow = glfwCreateWindow(k_width, k_height, "Learn OpenGL", nullptr, nullptr);

		// Setting screenWidth and screenHeight to Real Sizes
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(mWindow, &screenWidth, &screenHeight);

		if (nullptr == mWindow) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();

			mWindow = nullptr;

			return EXIT_FAILURE;
		}

		// Bind the declared window to the current context
		glfwMakeContextCurrent(mWindow);

		glewExperimental = GL_TRUE;

		if (GLEW_OK != glewInit()) {
			std::cout << "Failed to initialise GLEW" << std::endl;

			mWindow = nullptr;

			return EXIT_FAILURE;
		}

		// Define OpenGl Viewport to be the same size as the defined window
		glViewport(0, 0, screenWidth, screenHeight);

		return EXIT_SUCCESS;
	}

	int OpenGlLab::runTest() {
		if (mWindow == nullptr) {
			return EXIT_FAILURE;
		}

		float vertices[] = {
			// positions		// colors			// texture coords
			0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		GeometryGLObjects geometry = mEngine->generateGeometryGLObjects(vertices, sizeof(vertices), indices, sizeof(indices));

		Shader shader("lab_opengl/shaders/core.vs", "lab_opengl/shaders/core.fs");
		shader.use();

		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);

		mEngine->bindTexture("lab_opengl/Resources/container.jpg", "lab_opengl/Resources/awesomeface.png");

		while (!glfwWindowShouldClose(mWindow)) {
			glfwPollEvents();

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

			shader.setMatrix("transform", trans);

			mEngine->drawTriangles(geometry, 2);

			glfwSwapBuffers(mWindow);
		}

		mEngine->cleanGeometryGLObjects(geometry);

		//glDeleteBuffers(1, &triangle1.EBO);

		glfwTerminate();

		return EXIT_SUCCESS;
	}
}
}