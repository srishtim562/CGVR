#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int x1, y1, x2, y2, n, flag = 0;

void drawPixel(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawLine()
{
	int x = x1, y = y1, dx = x2 - x1, dy = y2 - y1;
	int incx, incy, inc1, inc2, e, i;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;

	incx = 1;
	incy = 1;
	if (x2 < x1)
		incx = -1;
	if (y2 < y1)
		incy = -1;

	if (dx > dy)		//Slope: m < 1
	{
		drawPixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		for (i = 0; i < dx; i++)
		{
			if (e < 0)
				e += inc1;
			else
			{
				e += inc2;
				y += incy;
			}
			x += incx;
			drawPixel(x, y);
		}
	}

	else
	{
		drawPixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		for (i = 0; i < dy; i++)
		{
			if (e < 0)
				e += inc1;
			else
			{
				e += inc2;
				x += incx;
			}
			y += incy;
			drawPixel(x, y);
		}
	}
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
		y1 = 250 - y;
		printf("Defining x1, y1: %d, %d\n", x1, y1);
		flag = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x2 = x - 250;
		y2 = 250 - y;
		printf("Defining x2, y2: %d, %d\n", x2, y2);
		flag = 0;
		drawLine();
	}
}

void displayMouse()
{}

void displayKeyboard()
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("Enter the values: x1, y1, x2, y2:\n");
		scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
		drawLine();
	}
}

int main(int argc, char **argv)
{
	int choice;
	printf("Press 1 for keyboard, 2 for mouse: ");
	scanf_s("%d", &choice);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	switch (choice)
	{
		case 1:		printf("Enter the no. of lines: ");
					scanf_s("%d", &n);
					glutCreateWindow("Bresenham's Line: Keyboard");
					myInit();
					glutDisplayFunc(displayKeyboard);
					break;

		case 2:		glutCreateWindow("Bresenham's Line: Mouse");
					myInit();
					glutMouseFunc(myMouse);
					glutDisplayFunc(displayMouse);
					break;

		default:	printf("Invalid Choice:\n");
					exit(0);
	}
	
	glutMainLoop();
}
