#pragma once

#include <memory>

namespace lab {
namespace opengl {

	struct GeometryGLObjects {
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
	};

	class OpenGlEngine {
	public:

		GeometryGLObjects generateGeometryGLObjects(float *vertices, int verticesLength, unsigned int* indices, int indiciesLength);
		GeometryGLObjects generateGeometryGLObjects(float *vertices, int verticesLength);

		void bindTexture(const char* textureFile1, const char* textureFile2);
		void drawTriangle(const GeometryGLObjects& objects, int vertices);
		void drawTriangles(const GeometryGLObjects& objects, int triangles, int vertices);
		void cleanGeometryGLObjects(const GeometryGLObjects& objects);
	};

}
}