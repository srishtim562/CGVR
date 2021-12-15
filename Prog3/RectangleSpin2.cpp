#include <GL/glut.h>
#include <math.h>

#define degToRad 180.0/3.14159

static GLfloat spin = 0.00;
GLfloat x, y;
int doubleb;

void spinDisplay()
{
	spin += 0.00025;
	if (spin > 360)
		spin -= 360;

	x = cos(degToRad * spin);
	y = sin(degToRad * spin);

	glutSetWindow(doubleb);
	glutPostRedisplay();
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1, 0, 0);
	gluOrtho2D(-2, 2, -2, 2);
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(spinDisplay);
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);
}

void square()
{
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(x, y);
		glColor3f(0, 1, 0);
		glVertex2f(-y, x);
		glColor3f(0, 0, 1);
		glVertex2f(-x, -y);
		glColor3f(1, 0, 1);
		glVertex2f(y, -x);
	glEnd();
}

void displaySingle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glFlush();
}

void displayDouble()
{
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Single Buffer");
	myInit();
	glutDisplayFunc(displaySingle);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	doubleb = glutCreateWindow("Double Buffer");
	myInit();
	glutMouseFunc(myMouse);
	glutDisplayFunc(displayDouble);
	glutIdleFunc(spinDisplay);

	glutMainLoop();
}
