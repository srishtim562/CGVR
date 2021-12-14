#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

int x1, yc1, x2, y2, r, flag = 0, n;

void drawPixel(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void plotPixels(int h, int k, int x, int y)
{
	drawPixel(x + h, y + k);
	drawPixel(-x + h, y + k);
	drawPixel(x + h, -y + k);
	drawPixel(-x + h, -y + k);
	drawPixel(y + h, x + k);
	drawPixel(-y + h, x + k);
	drawPixel(y + h, -x + k);
	drawPixel(-y + h, -x + k);
}

void drawCircle(int h, int k, int r)
{
	int d = 3 - 2 * r, x = 0, y = r;

	while (y > x)
	{
		plotPixels(h, k, x, y);
		if (d < 0)
			d = d + 4 * x + 6;
		else
		{
			d = d + 4 * (x - y) + 10;
			--y;
		}
		++x;
	}
	plotPixels(h, k, x, y);
	glFlush();
}

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	gluOrtho2D(-250, 250, -250, 250);
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 0)
	{
		x1 = x - 250;
		yc1 = 250 - y;
		flag = 1;
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x2 = x - 250;
		y2 = 250 - y;
		float exp = ((x2 - x1) * (x2 - x1)) + ((y2 - yc1) * (y2 - yc1));
		r = (int)(sqrt(exp));
		printf("Centre = (%d, %d), radius = %d\n", x1, yc1, r);
		drawCircle(x1, yc1, r);
		flag = 0;
	}
}

void displayMouse()
{}

void displayKey()
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("Enter coordinates of the centre, and the radius:\n");
		scanf_s("%d %d %d", &x1, &yc1, &r);
		drawCircle(x1, yc1, r);
	}
}

int main(int argc, char** argv)
{
	int choice;
	printf("Enter 1 for keyboard, 2 for mouse: ");
	scanf_s("%d", &choice);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	switch (choice)
	{
		case 1:		printf("Enter the no. of circles: ");
					scanf_s("%d", &n);
					glutCreateWindow("Bresenham's Circle: Keyboard");
					myInit();
					glutDisplayFunc(displayKey);
					break;

		case 2:		glutCreateWindow("Bresenham's Circle: Mouse");
					myInit();
					glutMouseFunc(myMouse);
					glutDisplayFunc(displayMouse);
					break;

		default:	printf("Invalid choice\n");
					exit(0);
	}
	glutMainLoop();
}
