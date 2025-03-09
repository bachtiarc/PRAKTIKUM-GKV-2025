// NAMA : CIKAL WAHYUNING BACHTIAR
// NIM : 24060123140175
// LAB : B1

// TUGAS PRAKTIKUM 2

#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

GLint b=300;
float  counter=600.0;
void initOpenGl()
{
    glClearColor(0.6, 0.4, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,700,0,500);
    glMatrixMode(GL_MODELVIEW);
}

void roda(int x,int y)
{
   float th;
   glBegin(GL_POLYGON);
   glColor3f(0,0,0);
   for(int i=0;i<360;i++)
   {
       th=i*(3.1416/180);
       glVertex2f(x+25*cos(th),y+25*sin(th));
   }

   glEnd();

}

void mobil()
{
   // Body
   glLoadIdentity();
   counter=counter-0.3;
   glTranslated(counter,100,0.0);

   glBegin(GL_POLYGON);
   glColor3f(0.96, 0.8, 0.86); // warna mobil pink kalem
   glVertex2f(100,100);
   glVertex2f(100,160);
   glVertex2f(450,160);
   glVertex2f(450,100);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(150,160);
   glVertex2f(200,200);
   glVertex2f(400,200);
   glVertex2f(450,160);
   glEnd();

   // Front window
   glBegin(GL_POLYGON);
   glColor3f(1.0, 1.0, 1.0); // warna putih
   glVertex2f(220,165);
   glVertex2f(220,190);
   glVertex2f(270,190);
   glVertex2f(270,165);
   glEnd();

   // Back window
   glBegin(GL_POLYGON);
   glColor3f(1.0, 1.0, 1.0); // warna putih
   glVertex2f(300,165);
   glVertex2f(300,190);
   glVertex2f(350,190);
   glVertex2f(350,165);
   glEnd();

   roda(200,100);
   roda(380,100);
}


void display()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.96, 0.8, 0.86);
  mobil();
  glutSwapBuffers();
  glFlush();


}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(700,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Mobil Pink Jalan");
    initOpenGl();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
