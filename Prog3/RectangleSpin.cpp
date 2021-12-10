#include <GL/glut.h>
#include <math.h>

#define degToRad 180.0/3.14159

static GLfloat spin = 0.0;
GLfloat x, y;
int doubleb;

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	gluOrtho2D(-2, 2, -2, 2);
}

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

void myMouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(spinDisplay);
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Single buffer");
	myInit();
	glutDisplayFunc(displaySingle);
	glutReshapeFunc(myReshape);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	doubleb = glutCreateWindow("Double buffer");
	myInit();
	glutDisplayFunc(displayDouble);
	glutReshapeFunc(myReshape);
	glutIdleFunc(spinDisplay);
	glutMouseFunc(myMouse);

	glutMainLoop();
}
