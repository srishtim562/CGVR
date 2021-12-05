#include <GL/glut.h>
#include <math.h>

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();

	float c = 3.142 / 180;
	float x, y, z, thetar, phir, phir20, phi, theta;

	for (phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		phir = c * phi;
		phir20 = c * (phi + 20);
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			thetar = c * theta;
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z);

			x = sin(thetar) * cos(phir20);
			y = cos(thetar) * cos(phir20);
			z = sin(phir20);
			glVertex3d(x, y, z);
		}
		glEnd();
	}

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, 1.0);
	float c80 = c * 80.0;
	z = sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, -1.0);
	z = -sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
	glFlush();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2);

	else
		glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2, -2, 2);

	glTranslatef(0, 0, -1);
	glRotatef(-45, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sphere");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}


