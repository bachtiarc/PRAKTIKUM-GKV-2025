// NAMA : CIKAL WAHYUNING BACHTIAR
// NIM : 24060123140175
// LAB : B1

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES



// GUNAKAN TOMBOL PANAH ATAS, BAWAH, KANAN, KIRI, HURUF S, DAN HURUF W
// UNTUK MELIAT MOBIL DARI POV SEGALA ARAH


float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float strafeX = 1.0f, strafeZ = 0.0f;
int deltaMove = 0, deltaStrafe = 0, deltaUpDown = 0, deltaRotate = 0, h, w;

void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void drawCar() {
    // Body utama (pink)
    glPushMatrix();
    glColor3f(1.0, 0.4, 0.6);
    glTranslatef(0, 0.3, 0);
    glScalef(2.0, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kabin
    glPushMatrix();
    glColor3f(0.9, 0.3, 0.5);
    glTranslatef(0, 0.7, 0);
    glScalef(1.2, 0.5, 0.8);
    glutSolidCube(1.0);
    glPopMatrix();

    // Jendela
    glColor3f(0.6, 0.8, 1.0);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(i * 0.6, 0.75, 0);
        glScalef(0.1, 0.3, 0.6);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Roda
    glColor3f(1.0, 1.0, 1.0);
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * 1.1, -0.1, j * 0.5);
            glRotatef(90, 0, 0, 1);
            glutSolidTorus(0.08, 0.25, 10, 30);

            // Jari-jari roda
            glColor3f(0.5, 0.5, 0.5);
            for (int k = 0; k < 6; k++) {
                glPushMatrix();
                glRotatef(k * 60, 0, 0, 1);
                glScalef(0.02, 0.25, 0.02);
                glutSolidCube(1.0);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }

    // Lampu depan
    glColor3f(1.0, 1.0, 0.0);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(1.05, 0.3, i * 0.4);
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.1, 10, 10);
        glPopMatrix();
    }

    // Lampu belakang
    glColor3f(1.0, 0.0, 0.0);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(-1.05, 0.3, i * 0.4);
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.1, 10, 10);
        glPopMatrix();
    }
}

void display() {
    if (deltaMove) {
        x += deltaMove * lx * 0.1;
        z += deltaMove * lz * 0.1;
    }
    if (deltaUpDown)
        y += deltaUpDown * 0.1;
    if (deltaRotate) {
        angle += deltaRotate * 2.0f;
        lx = sin(angle * M_PI / 180.0);
        lz = -cos(angle * M_PI / 180.0);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
    drawCar();
    glutSwapBuffers();
}

void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
        case GLUT_KEY_LEFT: deltaRotate = -1; break;
        case GLUT_KEY_RIGHT: deltaRotate = 1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0; break;
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaRotate = 0; break;
    }
}

void normalKey(unsigned char key, int x, int y) {
    if (key == 'w') deltaUpDown = 1;
    if (key == 's') deltaUpDown = -1;
}

void normalKeyUp(unsigned char key, int x, int y) {
    if (key == 'w' || key == 's') deltaUpDown = 0;
}

void lighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat light_position[] = { 0.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    lighting();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background putih
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil Pink Cikal Praktikum 4");
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutKeyboardFunc(normalKey);
    glutKeyboardUpFunc(normalKeyUp);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    init();
    glutMainLoop();
    return 0;
}
