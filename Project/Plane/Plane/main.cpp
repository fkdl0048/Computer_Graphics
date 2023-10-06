#include "Plane.h"

Plane plane;

bool bPlay = false;
float mytime = 0;

void myInit()
{
	plane.init();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	plane.draw(mytime);

	glutSwapBuffers();
}

void myIdle()
{
	if (bPlay != true) return;

	Sleep(16);
	mytime += 0.016f;

	glutPostRedisplay();
}

void myKeyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case ' ':	bPlay = !bPlay;			break;
	case '1':	plane.declineLength();	break;
	case '2':	plane.increaseLength();	break;
	case 'w':	plane.wave();			break;
	default:							break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment 01 - Plane");

	glewExperimental = true;
	glewInit();

	myInit();

	glutDisplayFunc(display);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return 0;
}

