#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Shader.h"

#include "OpenGLTest.h"

namespace lab {
namespace opengl {

	struct GeometryGLObjects {
		unsigned int VAO;
		unsigned int VBO;
	};

	const int k_width = 800;
	const int k_height = 600;

	OpenGLTest::OpenGLTest() : _window(nullptr) {}

	int OpenGLTest::initializeWindow() {
		glfwInit();

		// Window Properties
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Declaring window
		_window = glfwCreateWindow(k_width, k_height, "Learn OpenGL", nullptr, nullptr);

		// Setting screenWidth and screenHeight to Real Sizes
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(_window, &screenWidth, &screenHeight);

		if (nullptr == _window) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();

			_window = nullptr;

			return EXIT_FAILURE;
		}

		// Bind the declared window to the current context
		glfwMakeContextCurrent(_window);

		glewExperimental = GL_TRUE;

		if (GLEW_OK != glewInit()) {
			std::cout << "Failed to initialise GLEW" << std::endl;

			_window = nullptr;

			return EXIT_FAILURE;
		}

		// Define OpenGl Viewport to be the same size as the defined window
		glViewport(0, 0, screenWidth, screenHeight);

		return EXIT_SUCCESS;
	}

	GeometryGLObjects OpenGLTest::generateGeometryGLObjects(float *vertices, int length) {

		// Generate Vertex Objects
		unsigned int VBO, VAO;

		//GLuint EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//glGenBuffers(1, &EBO);

		// Bind Vertex Array Object (Interpretation of the geometry)
		glBindVertexArray(VAO);

		// Bind Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Copy buffer data for Buffer 
		glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);

		// Defines Vertex Attributes (Input for shaders)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Bind Element Buffer Object
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Copy Buffer Data For Element Buffer
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Unbind Element Buffer
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbind Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind Vertex Array Object
		glBindVertexArray(0);

		// Define Polygon Draw Mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		return { VAO, VBO };
	}

	void OpenGLTest::drawTriangle(const GeometryGLObjects& objects) {
		glBindVertexArray(objects.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
	}

	void OpenGLTest::cleanGeometryGLObjects(const GeometryGLObjects& objects) {
		glDeleteVertexArrays(1, &objects.VAO);
		glDeleteBuffers(1, &objects.VBO);
	}

	int OpenGLTest::runTest() {
		if (!_window) {
			return EXIT_FAILURE;
		}

		// Define Geometry
		float vertices[] = {
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		GeometryGLObjects triangle = generateGeometryGLObjects(vertices, sizeof(vertices));

		Shader shader("lab_opengl/OpenGLTest/shaders/core.vs", "lab_opengl/OpenGLTest/shaders/core.fs");
		shader.use();

		shader.setFloat("horizontalOffset", 0.5f);

		while (!glfwWindowShouldClose(_window)) {
			glfwPollEvents();

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			drawTriangle(triangle);

			glfwSwapBuffers(_window);
		}

		cleanGeometryGLObjects(triangle);

		//glDeleteBuffers(1, &triangle1.EBO);

		glfwTerminate();

		return EXIT_SUCCESS;
	}
}
}