#include <vgl.h>
#include <InitShader.h>
#include <vec.h>
#include "MyPlane.h"

float gTime = 0.1f;
bool gMove = false;
int gWave = 0;
GLuint prog;
MyPlane plane;

void init()
{
	plane.init();
	prog = InitShader("vShader.glsl", "fShader.glsl");
	glUseProgram(prog);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	plane.draw(prog, gTime, gWave);
	
	glutSwapBuffers();
}

void idle()
{
	if (gMove != true)
		return;

	Sleep(16);
	gTime += 0.016f;

	glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (plane.rect_length > 2)
		{
			plane.rect_length--;
			plane.init();
			display();
		}
		break;
	case '2':
		plane.rect_length++;
		plane.init();
		display();
		break;
	case 'w':
		if (gWave)
			gWave = 0;
		else
			gWave = 1;
		display();
		break;
	case 32:
		if (gMove)
			gMove = false;
		else
			gMove = true;
		display();
		break;
	case 'q':
		exit(0);
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment 01");

	glewExperimental = true;
	glewInit();

	init();
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyDown);

	glutMainLoop();

	return 0;
}