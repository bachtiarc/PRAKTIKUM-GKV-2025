//
//  main.cpp
//  PRAK3
//
//  Created by Cikal Wahyuning Bachtiar on 16/03/25.
//

// Nama     : Cikal Wahyuning Bachtiar
// NIM      : 24060123140175
// Lab      : B1

#include <GLUT/glut.h>
#include <cstdlib>

static int shoulder = 0, elbow = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, thumb = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawCube(float scaleX, float scaleY, float scaleZ) {
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawFinger(float x, float y, float rotation) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    drawCube(0.3, 0.1, 0.1);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Shoulder
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    drawCube(2.0, 0.4, 1.0);
    
    // Elbow
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    drawCube(2.0, 0.4, 1.0);
    
    // Palm
    glTranslatef(1.0, 0.0, 0.0);
    drawCube(1.0, 0.4, 0.8);
    
    // Fingers
    drawFinger(0.5, 0.2, finger1);
    drawFinger(0.5, 0.1, finger2);
    drawFinger(0.5, 0.0, finger3);
    drawFinger(0.5, -0.1, finger4);
    
    // Thumb (Agak ke bawah)
    glPushMatrix();
    glTranslatef(0.4, -0.2, 0.0);
    glRotatef(thumb, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    drawCube(0.3, 0.1, 0.1);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case '1': finger1 = (finger1 + 5) % 90; break;
        case '!': finger1 = (finger1 - 5) % 90; break;
        case '2': finger2 = (finger2 + 5) % 90; break;
        case '@': finger2 = (finger2 - 5) % 90; break;
        case '3': finger3 = (finger3 + 5) % 90; break;
        case '#': finger3 = (finger3 - 5) % 90; break;
        case '4': finger4 = (finger4 + 5) % 90; break;
        case '$': finger4 = (finger4 - 5) % 90; break;
        case 't': thumb = (thumb + 5) % 90; break;
        case 'T': thumb = (thumb - 5) % 90; break;
        case 27: std::exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tangan Robot Balok Cikal");

    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

