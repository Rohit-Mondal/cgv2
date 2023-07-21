#include <GL/glu.h>
#include <GL/glut.h>

GLfloat xMin = -0.5, xMax = 0.5, yMin = -0.5, yMax = 0.5;
GLfloat x1 = -0.7, y11 = -0.3, x2 = -0.6, y2 = 0.9;

int LEFT = 1, RIGHT = 2, BOT = 4, TOP = 8;
int C1, C2; 
int Clip_Flag = 0, Flag = 1;

int Get_Code(GLfloat x, GLfloat y)
{
    int Code = 0;
    if (x < xMin)
    {
        Code = Code | LEFT;
    }
    if (x > xMax)
    {
        Code = Code | RIGHT;
    }
    if (y < yMin)
    {
        Code = Code | BOT;
    }
    if (y > yMax)
    {
        Code = Code | TOP;
    }
    return Code;
}

void Clip()
{
    int C;
    GLfloat x, y;
    if (C1)
    {
        C = C1;
    }
    else
    {
        C = C2;
    }

    if (C & LEFT)
    {
        x = xMin;
        y = y11 + (y2 - y11) * ((xMin - x1) / (x2 - x1));
    }
    if (C & RIGHT)
    {
        x = xMax;
        y = y11 + (y2 - y11) * ((xMax - x1) / (x2 - x1));
    }
    if (C & BOT)
    {
        y = xMin;
        x = x1 + (x2 - x1) * ((yMin - x1) / (y2 - y11));
    }
    if (C & TOP)
    {
        y = yMax;
        x = x1 + (x2 - x1) * ((yMax - x1) / (y2 - y11));
    }

    if (C == C1)
    {
        x1 = x;
        y11 = y;
    }
    else
    {
        x2 = x;
        y2 = y;
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xMin, yMin);
    glVertex2f(xMax, yMin);
    glVertex2f(xMax, yMax);
    glVertex2f(xMin, yMax);
    glEnd();

    glColor3f(1, 0, 0);
    if (Flag == 1)
    {
        glBegin(GL_LINES);
        glVertex2f(x1, y11);
        glVertex2f(x2, y2);
        glEnd();
    }

    while (Clip_Flag == 1)
    {
        C1 = Get_Code(x1, y11);
        C2 = Get_Code(x2, y2);
        if ((C1|C2) == 0)
        {
            break;
        }
        else if ((C1&C2) != 0)
        {
            Flag = 0;
            break;
        }
        else
        {
            Clip();
        }
    }
    glFlush();
}

void Key(unsigned char ch, int x, int y)
{
    Clip_Flag = 1;
    glutPostRedisplay();
}

int main(int argC, char **argV)
{
    glutInit(&argC, argV);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Clip");
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutMainLoop();
    return 0;
}