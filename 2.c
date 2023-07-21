#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

GLfloat R;

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1, 0.4);
    glVertex2f(0.7, 0.4);
    glVertex2f(0.4, 0.8);
    glEnd();

    glLoadIdentity();
    glTranslatef(0.1, 0.4, 0);
    glRotatef(R, 0,0,1);
    glTranslatef(-0.1, -0.4, 0);

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1, 0.4);
    glVertex2f(0.7, 0.4);
    glVertex2f(0.4, 0.8);
    glEnd();

    glLoadIdentity();
    glTranslatef(0, 0, 0);
    glRotatef(R, 0,0,1);
    glTranslatef(-0, -0, 0);

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1, 0.4);
    glVertex2f(0.7, 0.4);
    glVertex2f(0.4, 0.8);
    glEnd();

    glFlush();
}

int main(int argC, char **argV)
{
    printf("Enter the Rotation Degree\n");
    scanf("%f", &R);
    glutInit(&argC, argV);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triangle");
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}