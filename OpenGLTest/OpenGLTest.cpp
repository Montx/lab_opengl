#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "OpenGLTest.h"

namespace opengl {

	const char* vertexShaderSource = "#version 330 core\n"
		"layout ( location = 0 ) in vec3 position;\n"
		"void main() {\n"
		"gl_Position = vec4( position.x, position.y, position.z, 1.0 );\n"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
		"}";

	const char* alternateFragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"color = vec4( 1.0f, 1.0f, 0.0f, 1.0f );\n"
		"}";

	struct GeometryObjects {
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

	GeometryObjects OpenGLTest::generateGeometryObjects(float *vertices, int length) {

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

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

	void OpenGLTest::drawTriangle(const GeometryObjects& objects) {
		glBindVertexArray(objects.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
	}

	void OpenGLTest::cleanGeometryObjects(const GeometryObjects& objects) {
		glDeleteVertexArrays(1, &objects.VAO);
		glDeleteBuffers(1, &objects.VBO);
	}

	int OpenGLTest::runTest() {
		if (!_window) {
			return EXIT_FAILURE;
		}

		int success;
		char infoLog[512];

		// Vertex Shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Fragment Shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Shader Program
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Define Geometry
		float vertices1[] = {
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			1.0f, -0.5f, 0.0f
		};

		float vertices2[] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-1.0f, -0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		GeometryObjects triangle1 = generateGeometryObjects(vertices1, sizeof(vertices1));

		GeometryObjects triangle2 = generateGeometryObjects(vertices2, sizeof(vertices2));

		// Defines Custom Shader Program
		glUseProgram(shaderProgram);

		while (!glfwWindowShouldClose(_window)) {
			glfwPollEvents();

			// Clear Screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			drawTriangle(triangle1);
			drawTriangle(triangle2);

			glfwSwapBuffers(_window);
		}

		cleanGeometryObjects(triangle1);
		cleanGeometryObjects(triangle2);

		//glDeleteBuffers(1, &triangle1.EBO);

		glfwTerminate();

		return EXIT_SUCCESS;
	}
}