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

	glutPostRedisplay(); // 다시 그리기 호출
}

void myKeyboard(unsigned char c, int x, int y)
{
	if (c == ' ')
		bPlay = !bPlay;

	if (c == '2')
	{
		plane.increaseLength();
		display();
	}
	if (c == '1')
	{
		plane.declineLength();
		display();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Color Cube Example");

	glewExperimental = true;
	glewInit();

	myInit();

	glutDisplayFunc(display);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return 0;
}

