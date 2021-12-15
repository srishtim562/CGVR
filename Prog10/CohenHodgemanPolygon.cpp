#include <stdio.h>
#include <GL/glut.h>

const int MAX_POINTS = 20;
int polySize, polyPoints[MAX_POINTS][2], orgPolySize, orgPolyPoints[MAX_POINTS][2], 
	clipperSize, clipperPoints[MAX_POINTS][2];

void drawPoly(int p[][2], int size)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < size; i++)
		glVertex2iv(p[i]);
	glEnd();
}

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - x2 * y1) * (x3 - x4) - (x1 - x2) * (x3 * y4 - x4 * y3);
	int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return num / den;
}

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - x2 * y1) * (y3 - y4) - (y1 - y2) * (x3 * y4 - x4 * y3);
	int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return num / den;
}

void clip(int polyPoints[][2], int &polySize, int x1, int y1, int x2, int y2)
{
	int newPoints[MAX_POINTS][2], newSize = 0;

	// (ix,iy),(kx,ky) are the co-ordinate values of the points
	for (int i = 0; i < polySize; i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % polySize;
		int ix = polyPoints[i][0], iy = polyPoints[i][1];
		int kx = polyPoints[k][0], ky = polyPoints[k][1];

		// Calculating position of first point w.r.t. clipper line
		int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);

		// Calculating position of second point w.r.t. clipper line
		int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		// Case 1 : When both points are inside
		if (i_pos < 0 && k_pos < 0)
		{
			//Only second point is added
			newPoints[newSize][0] = kx;
			newPoints[newSize][1] = ky;
			newSize++;
		}

		// Case 2: When only first point is outside
		else if (i_pos >= 0 && k_pos < 0)
		{
			// Point of intersection with edge and the second point is added
			newPoints[newSize][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoints[newSize][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newSize++;
			newPoints[newSize][0] = kx;
			newPoints[newSize][1] = ky;
			newSize++;
		}

		// Case 3: When only second point is outside
		else if (i_pos < 0 && k_pos >= 0)
		{
			//Only point of intersection with edge is added
			newPoints[newSize][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoints[newSize][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newSize++;
		}

		// Case 4: When both points are outside
		else
		{
			//No points are added
		}
	}

	// Copying new points into original array and changing the no. of vertices
	polySize = newSize;
	for (int i = 0; i < newSize; i++)
	{
		polyPoints[i][0] = newPoints[i][0];
		polyPoints[i][1] = newPoints[i][1];
	}
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(0, 500, 0, 500);
}

void display()
{
	init();
	glColor3f(1, 0, 0);
	drawPoly(clipperPoints, clipperSize);

	glColor3f(0, 1, 0);
	drawPoly(orgPolyPoints, orgPolySize);

	for (int i = 0; i < clipperSize; i++)
	{
		int k = (i + 1) % clipperSize;
		clip(polyPoints, polySize, clipperPoints[i][0], clipperPoints[i][1],
			clipperPoints[k][0], clipperPoints[k][1]);
	}

	glColor3f(0, 0, 1);
	drawPoly(polyPoints, polySize);
	glFlush();
}

int main(int argc, char** argv)
{
	printf("Enter no. of vertices of polygon: ");
	scanf_s("%d", &polySize);
	orgPolySize = polySize;
	printf("Enter the vertices:\n");
	for (int i = 0; i < polySize; i++)
	{
		printf("(x, y): ");
		scanf_s("%d %d", &polyPoints[i][0], &polyPoints[i][1]);
		orgPolyPoints[i][0] = polyPoints[i][0];
		orgPolyPoints[i][1] = polyPoints[i][1];
	}

	printf("Enter the no. of vertices of the clipping window: ");
	scanf_s("%d", &clipperSize);
	printf("Enter the vertices:\n");
	for (int i = 0; i < clipperSize; i++)
	{
		printf("(x, y): ");
		scanf_s("%d %d", &clipperPoints[i][0], &clipperPoints[i][1]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Polygon Clipping");
	glutDisplayFunc(display);
	glutMainLoop();
}
