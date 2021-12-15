#include <GL/glut.h>
#include <stdio.h>

int x1, y1, x2, y2, r;

void drawPixel(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
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
		if (d > 0)
		{
			d = d + 4 * (x - y) + 10;
			--y;
		}
		else
			d = d + 4 * x + 6;

		++x;
	}
	plotPixels(h, k, x, y);
	glFlush();
}

void drawCylinder()
{
	int i, n = 50, r = 50, x = 100, y = 100;
	for (i = 0; i < n; i += 3)
		drawCircle(x, y + i, r);
}

void quadrilateral(int x1, int x2, int y1, int y2)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1, y1);
		glVertex2i(x2, y1);
		glVertex2i(x2, y2);
		glVertex2i(x1, y2);
	glEnd();
}

void drawParallelepiped()
{
	int i, n = 40, x1 = 100, y1 = 100, x2 = 200, y2 = 175;
	for (i = 0; i < n; i += 2)
		quadrilateral(x1 + i, x2 + i, y1 + i, y2 + i);
}

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	gluOrtho2D(0, 400, 0, 300);
}

void display1()
{
	glColor3f(1.0, 0.0, 0.0);
	drawCylinder();
	glFlush();
}

void display2()
{
	glColor3f(0.0, 0.0, 1.0);
	drawParallelepiped();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Cylinder");
	myInit();
	glutDisplayFunc(display1);

	glutInitWindowSize(400, 300);
	glutInitWindowPosition(400, 0);
	glutCreateWindow("Parallelepiped");
	myInit();
	glutDisplayFunc(display2);

	glutMainLoop();
}
