#include <stdio.h>
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

GLfloat d = 0;
int a = 0;

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
}

void Mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON)
        a = 1;
    if (btn == GLUT_MIDDLE_BUTTON)
        a = 2;
    if (btn == GLUT_RIGHT_BUTTON)
        a = 3;
}

void Spin()
{
    d = d + 1;
    glutPostRedisplay();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    glColor3f(1, 0, 0);
    Face(V0, V1, V2, V3); // FRONT
    glColor3f(0, 1, 0);
    Face(V4, V5, V6, V7); // BACK
    glColor3f(0, 0, 1);
    Face(V0, V4, V7, V3); // LEFT
    glColor3f(1, 1, 0);
    Face(V1, V5, V6, V2); // RIGHT
    glColor3f(1, 0, 1);
    Face(V2, V3, V7, V6); // BOTTOM
    glColor3f(0, 1, 1);
    Face(V0, V1, V5, V4); // TOP
}

void Draw()
{
    GLfloat V[8][3] = {
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5},
        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
    };
    GLfloat rV[8][3], r;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    r = d * 3.14 / 180;

    if (a == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][0];
            rV[i][1] = V[i][1] * cos(r) - V[i][2] * sin(r);
            rV[i][2] = V[i][1] * sin(r) + V[i][2] * cos(r);
        }
        Cube(rV[0], rV[1], rV[2], rV[3], rV[4], rV[5], rV[6], rV[7]);
        glutSwapBuffers();
    }
    else if (a == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][2] * sin(r) + V[i][0] * cos(r);
            rV[i][1] = V[i][1];
            rV[i][2] = V[i][2] * cos(r) - V[i][0] * sin(r);
        }
        Cube(rV[0], rV[1], rV[2], rV[3], rV[4], rV[5], rV[6], rV[7]);
        glutSwapBuffers();
    }
    else if (a == 3)
    {
        for (int i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][0] * cos(r) - V[i][1] * sin(r);
            rV[i][1] = V[i][0] * sin(r) + V[i][1] * cos(r);
            rV[i][2] = V[i][2];
        }
        Cube(rV[0], rV[1], rV[2], rV[3], rV[4], rV[5], rV[6], rV[7]);
        glutSwapBuffers();
    }
    else
    {
        Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
        glutSwapBuffers();
    }
}

void MyInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Color Cube");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Spin);
    glutMouseFunc(Mouse);
    glutMainLoop();
    return 0;
}