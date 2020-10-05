#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

struct MaterialPoint
{
    float x,y,z;
    float vx,vy,vz;
    float ax,ay,az;
};
void moveMe(MaterialPoint *m)
{
    glTranslatef(m->x, m->y, m->z);
    m->vx+=m->ax;
    m->vy+=m->ay;
    m->vz+=m->az;

    m->x+=m->vx;
    m->y+=m->vy;
    m->z+=m->vz;
}
void initGL(int width, int height)
{
    const GLfloat ligth_ambient[]={0.0f, 0.0f, 0.0f, 1.0f};
    const GLfloat light_diffuse[]={1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_position[]={2.0f, 5.0f, 5.0f, 0.0f};
    const GLfloat light_specular[]={1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ligth_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 2.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}
static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,2.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}
static void
display(void)
{
    static MaterialPoint *miscare = new MaterialPoint;
        float t=0.0f;
    static int lasttime=0;
    int rightnow=glutGet(GLUT_ELAPSED_TIME);
    float dt=((float)(rightnow-lasttime))/1000.0f;
    t+=dt;
    lasttime=rightnow;
    static int frame,timebase=0;
    int time;
    char s[100];
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if(time-timebase>1000)
    {
        sprintf(s,"Viteza:%4.2f, Acceleratie: %4.2f, Durata: %f", miscare->vy,miscare->ay,t);
        glutSetWindowTitle(s);
        timebase=time;
        frame=0;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    static float axisRot=0.0f;
    static float globRotR=0.0f;
    static float globRotG=120.0f;
    static float globRotB=240.0f;
    static bool initMiscare = true;
    if (initMiscare)
        {
            miscare->vy=0.0001f;
            miscare->ay=-0.0001f;
            initMiscare = false;
        }

    /*glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -20);
    glRotatef(globRotR, 0, 0, 1);
    glTranslatef(5.0f, 0.0f, 0.0f);
    glRotatef(axisRot, 0, 1, 0);
    glutSolidCube(2);
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -20);
    glRotatef(globRotG, 0, 0, 1);
    glTranslatef(5.0f, 0.0f, 0.0f);
    glRotatef(axisRot, 0, 1, 0);
    glutSolidCube(2);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -20);
    glRotatef(globRotB, 0, 0, 1);
    glTranslatef(5.0f, 0.0f, 0.0f);
    glRotatef(axisRot, 0, 1, 0);
    glutSolidCube(2);
    glPopMatrix();*/

    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    moveMe(miscare);
    glTranslatef(0.0f, 7.0f, -20);

    glutSolidSphere(1,13,13);
    glPopMatrix();

    if(miscare->y<-5)
    {
        miscare->vy=0.0f;
        miscare->ay=0.0f;
    }
    axisRot+=1.0f; axisRot=fmod(axisRot, 360.0f);
    globRotR+=0.5f; globRotR=fmod(globRotR, 360.0f);
    globRotG+=0.5f; globRotG=fmod(globRotG, 360.0f);
    globRotB+=0.5f; globRotB=fmod(globRotB, 360.0f);

    glutSwapBuffers();
}

static void
idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    int width=640;
    int height=480;
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);
    initGL(width,height);

    glutMainLoop();
    return EXIT_SUCCESS;
}
