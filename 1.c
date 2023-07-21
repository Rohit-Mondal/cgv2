#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

GLfloat x1, y11, x2, y2;

void Draw(GLfloat x1, GLfloat y11, GLfloat x2, GLfloat y2)
{
    GLfloat M, p, dx, dy, x, y, t;
    glClear(GL_COLOR_BUFFER_BIT);

    if ((x2 - x1) == 0)
    {
        M = (y2 - y11);
    }
    else
    {
        M = (y2 - y11) / (x2 - x1);
    }

    if (fabs(M) < 1)
    {
        if (x1 > x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y11;
            y11 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y11);

        p = 2 * dy - dx;
        x = x1;
        y = y11;

        glBegin(GL_POINTS);
        while (x <= x2)
        {
            glVertex2f(x, y);
            x = x + 1;

            if (p >= 1)
            {
                if (M < 1)
                {
                    y = y + 1;
                }
                else
                {
                    y = y - 1;
                }
                p = p + 2 * dy - 2 * dx;
            }
            else
            {
                y = y;
                p = p + 2 * dy;
            }
        }
        glEnd();
    }

    if (fabs(M) >= 1)
    {
        if (y11 > y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y11;
            y11 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y11);

        p = 2 * dx - dy;
        x = x1;
        y = y11;

        glBegin(GL_POINTS);
        while (y <= y2)
        {
            glVertex2f(x, y);
            y = y + 1;

            if (p >= 1)
            {
                if (M > 1)
                {
                    x = x + 1;
                }
                else
                {
                    x = x - 1;
                }
                p = p + 2 * dx - 2 * dy;
            }
            else
            {
                x = x;
                p = p + 2 * dx;
            }
        }
        glEnd();
    }
}

void myDisplay()
{
    Draw(x1, y11, x2, y2);
    glFlush();
}

void MyInit()
{
    glClearColor(0,0,0,1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argC, char **argV)
{
    printf("Enter (x1, y11, x2, y2)\n");
    scanf("%f %f %f %f", &x1, &y11, &x2, &y2);
    glutInit(&argC, argV);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Brenhams Line Algo");
    MyInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}