#include "OpenGlLab.h"

#include "GLMTest.h"


int main() {
	
	lab::opengl::OpenGlLab lab;
	lab.initialize();

	return lab.runTest3();
}