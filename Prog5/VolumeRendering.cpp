/* Program to recursively divide a tetrahedron to form a 3D Sierpinski Gasket.
  The number of recursive steps is to be specified by the user. */
//Volume rendering

#include <stdio.h>
#include <GL/glut.h>
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600

 // point is now an array of 3 float values
typedef float point[3];

// Initial tetrahedron

point v[4] = {
	{0, 250, -250},
	{0, 0, 250},
	{250, -250, -250},
	{-250, -250, -250}
};

int n;

void triangle(point a, point b, point c)
{
	// Display 1 triangle
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void tetrahedron(point p1, point p2, point p3, point p4)
{
	glColor3f(1.0, 1.0, 0.0);
	triangle(p1, p2, p3);
	glColor3f(0.0, 1.0, 0.0);
	triangle(p1, p3, p4);
	glColor3f(1.0, 0.0, 0.0);
	triangle(p1, p2, p4);
	glColor3f(0.0, 0.0, 1.0);
	triangle(p2, p3, p4);
}


void divideTetrahedron(point p1, point p2, point p3, point p4, int m)
{
	point mid[6];
	int i;

	if (m > 0)
	{
		for (i = 0; i < 3; i++)
		{
			mid[0][i] = (p1[i] + p2[i]) / 2;
			mid[1][i] = (p1[i] + p3[i]) / 2;
			mid[2][i] = (p1[i] + p4[i]) / 2;
			mid[3][i] = (p2[i] + p3[i]) / 2;
			mid[4][i] = (p3[i] + p4[i]) / 2;
			mid[5][i] = (p2[i] + p4[i]) / 2;
		}

		divideTetrahedron(p1, mid[0], mid[1], mid[2], m - 1);
		divideTetrahedron(mid[0], p2, mid[3], mid[5], m - 1);
		divideTetrahedron(mid[1], mid[3], p3, mid[4], m - 1);
		divideTetrahedron(mid[2], mid[4], mid[5], p4, m - 1);
	}

	else
	{
		// Draw a tetrahedron at the end of the recursion
		tetrahedron(p1, p2, p3, p4);
	}
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divideTetrahedron(v[0], v[1], v[2], v[3], n);
	glEnd();
	glFlush();
}


void main(int argc, char** argv)
{
	printf("No. of divisions: ");
	scanf_s("%d", &n);
	glutInit(&argc, argv);
	// To view the behind triangle, GLUT_DEPTH is for hidden surface removal
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("3D Gasket");
	myInit();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
