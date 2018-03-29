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
		GeometryGLObjects generateGeometryGLObjects(float *vertices, int verticesLength, unsigned int* indices, int indiciesLength);

		void drawTriangle(const GeometryGLObjects& objects);
		void drawTriangles(const GeometryGLObjects& objects, int triangles);
		void cleanGeometryGLObjects(const GeometryGLObjects& objects);
		void bindTexture(const char* textureFile1, const char* textureFile2);

		GLFWwindow* _window;
	};

}
}