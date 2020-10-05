#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
struct MaterialPoint {
    float x, y, z; //pozitie
    float vx, vy, vz; //viteza
    float ax, ay, az; //acceleratie
};

void moveMe(MaterialPoint *m) {
     glTranslatef(m->x, m->y, m->z);

     m->vx += m->ax;
     m->vy += m->ay;
     m->vz += m->az;

     m->x += m->vx;
     m->y += m->vy;
     m->z += m->vz;
}

void initGL(int width, int height) {
     const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
     const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
     const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
     const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHTING);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
     glLightfv(GL_LIGHT0, GL_POSITION, light_position);

     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);

     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LESS);

     glEnable(GL_COLOR_MATERIAL);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,
     2.0f, 100.0f);
     glMatrixMode(GL_MODELVIEW);
}

static void display(void) {
    static int frame,timebase=0;
    int time;
    char s[100];
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        sprintf(s,"[FPS:%4.2f] Lab 2: Imagine+Imagine+Imagine+...= Animatie !",frame*1000.0/(time-timebase));
        glutSetWindowTitle(s);
        timebase = time;
        frame = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); //initializarea sistemului de coordonate

    static float axisRot = 0.0f;
    static float globRotR = 0.0f;
    static float globRotG = 120.0f;
    static float globRotB = 240.0f;
    static MaterialPoint *miscare = new MaterialPoint;

    static bool initMiscare = true;
    if (initMiscare)
    {
        miscare->z=1.0f;
        miscare->az=0.00001f;
        initMiscare = false;
    }

    glColor3f(0.0f, 0.5f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -20);
    glRotatef(globRotG, 0, 0, 1);
    glTranslatef(5.0f, 0.0f, 0.0f);
    glRotatef(axisRot, 0, 1, 0);
    glutWireSphere(1,15,15); //cub cu latura 2
    glPopMatrix();


    axisRot += 0.4f; axisRot=fmod(axisRot, 360.0f);
    globRotR += 0.5f; globRotR=fmod(globRotR, 360.0f);
    globRotG += 0.5f; globRotG=fmod(globRotG, 360.0f);
    globRotB += 0.0f; globRotB=fmod(globRotB, 360.0f);

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}
/* Punct de intrare in program */
int main(int argc, char *argv[])
{
    int width = 640;
    int height = 480;
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(""); //titlu vid, il setez in display()
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    initGL(width, height);
    glutMainLoop();
    return EXIT_SUCCESS;
}
