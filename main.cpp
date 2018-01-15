#include "OpenGLTest.h"


int main() {
	
	opengl::OpenGLTest test;
	test.initializeWindow();

	return test.runTest();
}