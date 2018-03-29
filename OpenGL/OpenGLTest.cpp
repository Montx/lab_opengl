#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "stb_image_definitions.h"

#include "Shader.h"

#include "OpenGLTest.h"

namespace lab {
namespace opengl {

	struct GeometryGLObjects {
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
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

	GeometryGLObjects OpenGLTest::generateGeometryGLObjects(float *vertices, int verticesLength, unsigned int* indices, int indiciesLength) {

		// Generate Vertex Objects
		unsigned int VBO, VAO, EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glGenBuffers(1, &EBO);

		// Bind Vertex Array Object (Interpretation of the geometry)
		glBindVertexArray(VAO);

		// Bind Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Copy buffer data for Buffer 
		glBufferData(GL_ARRAY_BUFFER, verticesLength, vertices, GL_STATIC_DRAW);

		// Bind Element Buffer Object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Copy Buffer Data For Element Buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesLength, indices, GL_STATIC_DRAW);

		// Defines Vertex Attributes (Input for shaders)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Unbind Element Buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbind Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind Vertex Array Object
		glBindVertexArray(0);

		// Define Polygon Draw Mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		return { VAO, VBO, EBO };
	}

	void OpenGLTest::drawTriangle(const GeometryGLObjects& objects) {
		glBindVertexArray(objects.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, objects.VBO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OpenGLTest::drawTriangles(const GeometryGLObjects& objects, int triangles) {
		glBindVertexArray(objects.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, objects.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects.EBO);

		glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OpenGLTest::cleanGeometryGLObjects(const GeometryGLObjects& objects) {
		glDeleteVertexArrays(1, &objects.VAO);
		glDeleteBuffers(1, &objects.VBO);
		glDeleteBuffers(1, &objects.EBO);
	}

	int OpenGLTest::runTest() {
		if (!_window) {
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

		GeometryGLObjects geometry = generateGeometryGLObjects(vertices, sizeof(vertices), indices, sizeof(indices));

		Shader shader("lab_opengl/shaders/core.vs", "lab_opengl/shaders/core.fs");
		shader.use();

		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);

		bindTexture("lab_opengl/Resources/container.jpg", "lab_opengl/Resources/awesomeface.png");

		while (!glfwWindowShouldClose(_window)) {
			glfwPollEvents();

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			drawTriangles(geometry, 2);

			glfwSwapBuffers(_window);
		}

		cleanGeometryGLObjects(geometry);

		//glDeleteBuffers(1, &triangle1.EBO);

		glfwTerminate();

		return EXIT_SUCCESS;
	}

	void OpenGLTest::bindTexture(const char* textureFile1, const char* textureFile2) {

		// Texture Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Texture Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Texture 1
		unsigned int texture1;
		glGenTextures(1, &texture1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(textureFile1, &width, &height, &nrChannels, 0);

		if (!data) {
			std::cout << "Could not load texture!" << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		// Texture 2
		unsigned int texture2;
		glGenTextures(1, &texture2);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		data = stbi_load(textureFile2, &width, &height, &nrChannels, 0);

		if (!data) {
			std::cout << "Could not load texture!" << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}
}