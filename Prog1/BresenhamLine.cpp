#include <GL/glut.h>
#include <stdio.h>

int x1, x2, y1, y2, n;
int flag = 0;
void drawPixel(int x, int y)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawLine()     //Bresenham's Algorithm
{
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < y1)
        incy = -1;
    x = x1;
    y = y1;
    if (dx > dy)    //Slope: m < 1
    {
        drawPixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (e > 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            drawPixel(x, y);
        }
    }
    else
    {
        drawPixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (e > 0)
            {
                x += incx;
                e += inc1;

            }
            else
                e += inc2;
            
            y += incy;
            drawPixel(x, y);
        }
    }
    glFlush();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-250, 250, -250, 250);
}

void myMouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (flag == 0)
                {
                    printf("Defining x1, y1: ");
                    x1 = x - 250;
                    y1 = 250 - y;
                    flag++;
                    printf("%d %d\n", x1, y1);
                }
                else
                {
                    printf("Defining x2, y2: ");
                    x2 = x - 250;
                    y2 = 250 - y;
                    flag = 0;
                    printf("%d %d\n", x2, y2);
                    drawLine();
                }
            }
            break;
        }
}

void display()
{}

void displayKey()
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter points: x1, y1, x2, y2\n");
        scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
        drawLine();
    }
}

int main(int argc, char **argv)
{

    //FOR KEYBOARD
   // printf("Enter number of lines: \n");
   // scanf_s("%d", &n);
    //END KEYBOARD

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("LINE");
    myInit();
    glutMouseFunc(myMouse); //INCLUDE TO USE MOUSE, REMOVE WHILE USING KEYBOARD
    glutDisplayFunc(display);
    //glutDisplayFunc(displayKey);//INCLUDE TO USE KEYBOARD, REMOVE WHILE USING MOUSE
    glutMainLoop();
}
