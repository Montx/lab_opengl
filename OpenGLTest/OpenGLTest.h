#pragma once

struct GLFWwindow;

namespace lab {
namespace opengl {

	struct GeometryGLObjects;

	class OpenGLTest {
	public:
		OpenGLTest();

		int initializeWindow();

		int runTest();

	private:
		GeometryGLObjects generateGeometryGLObjects(float *vertices, int length);

		void drawTriangle(const GeometryGLObjects& objects);
		void cleanGeometryGLObjects(const GeometryGLObjects& objects);

		GLFWwindow* _window;
	};

}
}