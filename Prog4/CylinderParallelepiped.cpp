#include <GL/glut.h>

void drawPixel(int x, int y)
{
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

void drawCylinder()
{
	int xc = 100, yc = 100, r = 50, n = 50;
	for (int i = 0; i < n; i += 3)
		drawCircle(xc, yc + i, r);
}

void parallelepiped(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
		glVertex2i(x2, y1);
	glEnd();
}

void drawParallelepiped()
{
	int x1 = 100, y1 = 175, x2 = 300, y2 = 300, n = 40;
	for (int i = 0; i < n; i += 2)
		parallelepiped(x1 + i, y1 + i, x2 + i, y2 + i);
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

void display1()
{
	glColor3f(1, 0, 0);
	drawCylinder();
	glFlush();
}

void display2()
{
	glColor3f(0, 0, 1);
	drawParallelepiped();
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cylinder");
	init();
	glutDisplayFunc(display1);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Parallelepiped");
	init();
	glutDisplayFunc(display2);

	glutMainLoop();
}
