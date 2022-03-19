#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <corecrt_math.h>

int r, xc, yc, x2, y2, flag, n;

void drawPixel(int x, int y)
{
	glColor3f(1, 0, 0);
	glPointSize(3.0);
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
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
		plotPixels(h, k, x, y);
	}
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 0)
	{ 
		xc = x - 250;
		yc = 250 - y;
		printf("Defining xc, yc = (%d, %d)\n", xc, yc);
		flag = 1;
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x2 = x - 250;
		y2 = 250 - y;
		float exp = (x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc);
		r = (int)sqrt(exp);
		printf("Defining r = %d\n", r);
		flag = 0;
		drawCircle(xc, yc, r);
	}
}

void displayMouse()
{}

void displayKeyboard()
{
	for (int i = 0; i < n; i++)
	{
		printf("Enter xc, yc, r\n");
		scanf_s("%d %d %d", &xc, &yc, &r);
		drawCircle(xc, yc, r);
	}
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

void main(int argc, char** argv)
{
	int choice;
	printf("Press 1 for keyboard, 2 for mouse: ");
	scanf_s("%d", &choice);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	switch (choice)
	{
		case 1:		printf("Enter the number of circles: ");
				scanf_s("%d", &n);
				glutCreateWindow("Bresenham's Circle: Keyboard");
				init();
				glutDisplayFunc(displayKeyboard);
				break;

		case 2: 	glutCreateWindow("Bresenham's Circle: Mouse");
				init();
				glutMouseFunc(myMouse);
				glutDisplayFunc(displayMouse);
				break;

		default: 	printf("Invalid choice\n");
				exit(0);
	}
	glutMainLoop();
}
