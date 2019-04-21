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

		void bindTexture(const char* textureFile1, const char* textureFile2);
		void drawTriangle(const GeometryGLObjects& objects);
		void drawTriangles(const GeometryGLObjects& objects, int triangles);
		void cleanGeometryGLObjects(const GeometryGLObjects& objects);
	};

}
}