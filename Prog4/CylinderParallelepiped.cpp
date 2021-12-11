#include <GL/glut.h>
#include <stdio.h>

void drawPixel(GLint cx, GLint cy)
{
	glColor3f(1.0, 0.0, 0.0);
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
	
void drawCylinder()		//By repeating circles
{
	GLint xc = 100, yc = 100, r = 50, n = 50, i;
	for (i = 0; i < n; i += 3)
		drawCircle(xc, yc + i, r);
}

void parallelepiped(int x1, int x2, int y1, int y2)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1, y1);
		glVertex2i(x2, y1);
		glVertex2i(x2, y2);
		glVertex2i(x1, y2);
	glEnd();
}

void drawParallelepiped()	//By repeating quadrilaterals
{
	int x1 = 200, x2 = 300, y1 = 100, y2 = 175, n = 40, i;
	for (i = 0; i < n; i += 2)
		parallelepiped(x1 + i, x2 + i, y1 + i, y2 + i);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void display1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	drawCylinder();
	glFlush();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	drawParallelepiped();
	glFlush();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Cylinder");
	init();
	glutDisplayFunc(display1);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(400, 0);
	glutCreateWindow("Parallelepiped");
	init();
	glutDisplayFunc(display2);
	glutMainLoop();
}
