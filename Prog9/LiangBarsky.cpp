#include <stdio.h>
#include <GL/glut.h>

double xmin, ymin, xmax, ymax; //50 50 100 100
double xvmin, yvmin, xvmax, yvmax; //200 200 300 300
int n;

struct lineSegment {
	int x1, y1, x2, y2;
};
struct lineSegment ls[10];

int cliptest(double p, double q, double* u1, double* u2)
{
	double r;
	if (p) r = q / p;  
	if (p < 0.0)    // potentially entry point, update te
	{
		if (r > *u1)
			*u1 = r;
		if (r > *u2) 
			return(false); // line portion is outside
	}
	else
	{
		if (p > 0.0)    //  Potentially leaving point, update tl
		{
			if (r < *u2)
				*u2 = r;
			if (r < *u1)
				return(false); // line portion is outside
		}
		else
			if (p == 0.0)
			{
				if (q < 0.0) 
					return(false); // line parallel to edge but outside
			}
	}
	return(true);
}

void LiangBarskyLineClipAndDraw(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1, dy = y2 - y1, u1 = 0.0, u2 = 1.0;
	//draw a red colored viewport
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
	glEnd();
	if (cliptest(-dx, x1 - xmin, &u1, &u2))  // inside test wrt left edge
		if (cliptest(dx, xmax - x1, &u1, &u2)) // inside test wrt right edge
			if (cliptest(-dy, y1 - ymin, &u1, &u2)) // inside test wrt bottom edge
				if (cliptest(dy, ymax - y1, &u1, &u2)) // inside test wrt top edge
				{
					if (u2 < 1.0)
					{
						x2 = x1 + u2 * dx;
						y2 = y1 + u2 * dy;
					}
					if (u1 > 0.0)
					{
						x1 = x1 + u1 * dx;
						y1 = y1 + u1 * dy;
					}
					// Window to viewport mappings
					double sx = (xvmax - xvmin) / (xmax - xmin); // Scale parameters
					double sy = (yvmax - yvmin) / (ymax - ymin);
					double vx1 = xvmin + (x1 - xmin) * sx;
					double vy1 = yvmin + (y1 - ymin) * sy;
					double vx2 = xvmin + (x2 - xmin) * sx;
					double vy2 = yvmin + (y2 - ymin) * sy;

					glColor3f(0.0, 0.0, 1.0); // draw blue colored clipped line
					glBegin(GL_LINES);
						glVertex2d(vx1, vy1);
						glVertex2d(vx2, vy2);
					glEnd();
				}
}// end of line clipping

void display()
{
	//draw a blue colored window
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmax, ymin);
		glVertex2f(xmax, ymax);
		glVertex2f(xmin, ymax);
	glEnd();

	//draw the line with red color
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
			glVertex2d(ls[i].x1, ls[i].y1);
			glVertex2d(ls[i].x2, ls[i].y2);
		glEnd();
	}
	
	for (int i = 0; i < n; i++)
		LiangBarskyLineClipAndDraw(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
	glFlush();
}

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	printf("Enter window coordinates: (xmin ymin xmax ymax): \n");
	scanf_s("%lf%lf%lf%lf", &xmin, &ymin, &xmax, &ymax);
	printf("Enter viewport coordinates: (xvmin yvmin xvmax yvmax): \n");
	scanf_s("%lf%lf%lf%lf", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("Enter no. of lines: ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
	{
		printf("Enter coordinates: (x1 y1 x2 y2):\n");
		scanf_s("%d%d%d%d", &ls[i].x1, &ls[i].y1, &ls[i].x2, &ls[i].y2);
	}

	glutCreateWindow("Liang Barsky Line Clipping Algorithm");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
