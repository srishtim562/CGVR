#include <GL/glut.h>
#include <stdio.h>

#define outcode int

const int TOP = 1, BOTTOM = 2, RIGHT = 4, LEFT = 8;

int n;
double xmin, xmax, ymin, ymax;
double xvmin, xvmax, yvmin, yvmax;

struct lineSegment
{
	int x1, y1, x2, y2;
};
struct lineSegment ls[10];

outcode computeOutcode(double x, double y)
{
	outcode code = 0;
	if (y > ymax)
		code |= TOP;
	if (y < ymin)
		code |= BOTTOM;
	if (x > xmax)
		code |= RIGHT;
	if (x < xmin)
		code |= LEFT;
	return code;
}

void cohenSuther(double x1, double y1, double x2, double y2)
{
	outcode outcode1, outcode2, outcodeout;
	bool accept = false, done = false;

	outcode1 = computeOutcode(x1, y1);
	outcode2 = computeOutcode(x2, y2);

	do
	{
		if (!(outcode1 | outcode2))
		{
			accept = true;
			done = true;
		}
		else if (outcode1 & outcode2)
			done = true;
		else
		{
			double x, y;
			outcodeout = outcode1 ? outcode1 : outcode2;
			if (outcodeout & TOP)
			{
				y = ymax;
				x = x1 + (ymax - y1) * (x2 - x1) / (y2 - y1);
			}
			else if (outcodeout & BOTTOM)
			{
				y = ymin;
				x = x1 + (ymin - y1) * (x2 - x1) / (y2 - y1);
			}
			else if (outcodeout & RIGHT)
			{
				x = xmax;
				y = y1 + (xmax - x1) * (y2 - y1) / (x2 - x1);
			}
			else
			{
				x = xmin;
				y = y1 + (xmin - x1) * (y2 - y1) / (x2 - x1);
			}

			if (outcodeout == outcode1)
			{
				x1 = x;
				y1 = y;
				outcode1 = computeOutcode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				outcode2 = computeOutcode(x2, y2);
			}
		}

	} while (!done);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);	//Viewport
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
	glEnd();

	if (accept)
	{
		double sx = (xvmax - xvmin) / (xmax - xmin);	//Scaling
		double sy = (yvmax - yvmin) / (ymax - ymin);
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;
		double vx2 = xvmin + (x2 - xmin) * sx;
		double vy2 = yvmin + (y2 - ymin) * sy;

		glColor3f(0, 0, 1);		
			glBegin(GL_LINES);		//Lines
			glVertex2d(vx1, vy1);
			glVertex2d(vx2, vy2);
		glEnd();
	}
}

void myInit()
{
	glClearColor(1, 1, 1, 0);
	glColor3f(1, 0, 0);
	glPointSize(1.0);
	gluOrtho2D(0, 500, 0, 500);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);		//Window
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymax);
		glVertex2f(xmax, ymax);
		glVertex2f(xmax, ymin);
	glEnd();

	for (int i = 0; i < n; i++)
	{
		glBegin(GL_LINES);	//Lines
			glVertex2d(ls[i].x1, ls[i].y1);
			glVertex2d(ls[i].x2, ls[i].y2);
		glEnd();
	}

	for (int i = 0; i < n; i++)
		cohenSuther(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);

	glFlush();
}

int main(int argc, char** argv)
{
	printf("Enter window coordinates: (xmin, ymin, xmax, ymax):\n");
	scanf_s("%lf %lf %lf %lf", &xmin, &ymin, &xmax, &ymax);
	printf("Enter viewport coordinates: (xvmin, yvmin, xvmax, yvmax):\n");
	scanf_s("%lf %lf %lf %lf", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("Enter no. of lines: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Enter line endpoints: (x1, y1, x2, y2):\n");
		scanf_s("%d %d %d %d", &ls[i].x1, &ls[i].y1, &ls[i].x2, &ls[i].y2);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cohen Sutherland Line Clipping");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}
