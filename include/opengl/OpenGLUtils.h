#pragma once

namespace lab {
namespace opengl {
	
	// Return the maximum number of vertex inputs that the current hardware supports.
	// This often returns the minimum of 16.
	int getMaxSupportedVertexInputs();

}
}