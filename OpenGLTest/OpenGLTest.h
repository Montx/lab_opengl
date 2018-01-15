#pragma once

struct GLFWwindow;

namespace opengl {

	struct GeometryObjects;

	class OpenGLTest {
	public:
		OpenGLTest();

		int initializeWindow();

		int runTest();
	
	private:
		GeometryObjects generateGeometryObjects(float *vertices, int length);

		void drawTriangle(const GeometryObjects& objects);
		void cleanGeometryObjects(const GeometryObjects& objects);

		GLFWwindow* _window;
	};

}