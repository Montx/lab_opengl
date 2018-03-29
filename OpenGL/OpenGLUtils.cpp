#include <GL/glew.h>

#include "OpenGLUtils.h"

namespace lab {
namespace opengl {

	int getMaxSupportedVertexInputs() {
		int nrVertex;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrVertex);
		return nrVertex;
	}

}
}