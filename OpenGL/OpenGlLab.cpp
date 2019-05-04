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

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

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

	void OpenGlLab::processInput(GLFWwindow *window)
	{
		float cameraSpeed = 2.5f * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			mCameraPos += cameraSpeed * mCameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			mCameraPos -= cameraSpeed * mCameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			mCameraPos -= glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			mCameraPos += glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed;
	}

	int OpenGlLab::runTest1() {
		if (mWindow == nullptr) {
			return EXIT_FAILURE;
		}

		glEnable(GL_DEPTH_TEST);

		float verticesPlane[] = {
			// positions		// colors			// texture coords
			0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
		};

		float verticesCube[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		GeometryGLObjects geometry = mEngine->generateGeometryGLObjects(verticesCube, sizeof(verticesCube));

		Shader shader("lab_opengl/shaders/core.vs", "lab_opengl/shaders/core.fs");
		shader.use();

		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);

		mEngine->bindTexture("lab_opengl/Resources/container.jpg", "lab_opengl/Resources/awesomeface.png");

		mCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		while (!glfwWindowShouldClose(mWindow)) {
			glfwPollEvents();

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(mWindow);

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), static_cast<float>(k_width / k_height), 0.1f, 100.0f);

			shader.setMatrix("view", view);
			shader.setMatrix("projection", projection);

			for (unsigned int i = 0; i < 10; i++) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f * i+1), glm::vec3(0.5f, 1.0f, 0.0f));

				shader.setMatrix("model", model);

				mEngine->drawTriangle(geometry, 36);
			}

			glfwSwapBuffers(mWindow);
		}

		mEngine->cleanGeometryGLObjects(geometry);

		glfwTerminate();

		return EXIT_SUCCESS;
	}

	int OpenGlLab::runTest2() {
		if (mWindow == nullptr) {
			return EXIT_FAILURE;
		}

		glEnable(GL_DEPTH_TEST);

		float verticesPlane[] = {
			// positions		// colors			// texture coords
			0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
		};

		float verticesCube[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		GeometryGLObjects geometry = mEngine->generateGeometryGLObjects(verticesCube, sizeof(verticesCube));

		Shader shader("lab_opengl/shaders/core.vs", "lab_opengl/shaders/core.fs");
		shader.use();

		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);

		mEngine->bindTexture("lab_opengl/Resources/container.jpg", "lab_opengl/Resources/awesomeface.png");

		while (!glfwWindowShouldClose(mWindow)) {
			glfwPollEvents();

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), static_cast<float>(k_width / k_height), 0.1f, 100.0f);

			shader.setMatrix("view", view);
			shader.setMatrix("projection", projection);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			shader.setMatrix("model", model);

			mEngine->drawTriangle(geometry, 36);

			glfwSwapBuffers(mWindow);
		}

		mEngine->cleanGeometryGLObjects(geometry);

		glfwTerminate();

		return EXIT_SUCCESS;
	}
}
}