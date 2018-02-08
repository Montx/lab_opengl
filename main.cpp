#include "OpenGLTest.h"


int main() {
	
	lab::opengl::OpenGLTest test;
	test.initializeWindow();

	return test.runTest();
}