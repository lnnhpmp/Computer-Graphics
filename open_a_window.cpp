#include <GL\freeglut.h>
#include "open_a_window.h"

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void InitializeGlutCallbacks() {
	glutDisplayFunc(RenderSceneCB);
}

void CreateNewWindow(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Configure some GLUT options
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// Specify the window parameters and create it
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("01");

	InitializeGlutCallbacks();

	glClearColor(0.f, 0.f, 0.f, 0.f);

	glutMainLoop();
}
