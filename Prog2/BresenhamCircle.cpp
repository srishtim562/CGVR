#include <GL/glut.h>
#include <stdio.h>
#include <corecrt_math.h>

int xc, yc, r, flag = 0, n, i;
int x1, yc1, x2, y2;

void drawPixel(GLint cx, GLint cy)
{
	glBegin(GL_POINTS);
		glVertex2i(cx, cy);
	glEnd();
}

void plotPixels(GLint h, GLint k, GLint x, GLint y)
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

void drawCircle(GLint h, GLint k, GLint r)	//Bresenham's circle drawing algorithm
{
	GLint d = 3 - 2 * r, x = 0, y = r;

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
		xc = x1;
		yc = yc1;
		float exp = ((x2 - x1) * (x2 - x1)) + ((y2 - yc1) * (y2 - yc1));
		r = (int)(sqrt(exp));
		printf("Defining centre = (%d, %d), radius = %d\n", xc, yc, r);
		drawCircle(xc, yc, r);
		flag = 0;
	}
}

void displayMouse()
{}

void displayKeyboard()
{
	for (i = 0; i < n; i++)
	{
		printf("Enter coordinates of the center (X, Y), and the radius (R):\n");
		scanf_s("%d %d %d", &xc, &yc, &r);
		drawCircle(xc, yc, r);
	}
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(3.0);
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

int main(int argc, char** argv)
{
	int choice;
	printf("Enter 1 for keyboard, 2 for mouse: ");
	scanf_s("%d", &choice);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	switch (choice)
	{
		case 1:	printf("Enter the number of circles: ");
				scanf_s("%d", &n);
				glutCreateWindow("Bresenham's Circle Keyboard");
				myInit();
				glutDisplayFunc(displayKeyboard);
				break;

		case 2: glutCreateWindow("Bresenham's Circle Mouse");
				myInit();
				glutMouseFunc(myMouse);
				glutDisplayFunc(displayMouse);
				break;

		default: printf("Invalid choice\n");
	}

	glutMainLoop();
}
