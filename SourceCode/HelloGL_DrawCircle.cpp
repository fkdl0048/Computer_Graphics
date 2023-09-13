#include <vgl.h>
#include <stdio.h>
#include <math.h>

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	int div = 200;
	float radius = 0.7f;
	float dtheta = 2*3.141592 / div;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < div; i++)
	{
		glColor3f((float)i / div, 0, 1 - (float)i / div);

		float x1 = radius * cos(i * dtheta);
		float y1 = radius * sin(i * dtheta);
		float x2 = radius * cos((i+1) * dtheta);
		float y2 = radius * sin((i+1) * dtheta);
		glVertex2f(0, 0);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Hello GL");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}