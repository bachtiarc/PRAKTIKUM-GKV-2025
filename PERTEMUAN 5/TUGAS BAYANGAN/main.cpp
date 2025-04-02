//
//  main.cpp
//  p5_bayangan
//
//  Created by Cikal Wahyuning Bachtiar on 02/04/25.
//

// Nama: Cikal Wahyuning Bachtiar
// NIM: 24060123140175
// Lab: GKV B1

#include <math.h>
#include <stdio.h>
#include <GLUT/glut.h>

double rx = 0.0;
double ry = 0.0;
float x = 0.0, y = 3.0, z = 30.0;  // Posisi kamera
float lx = 0.0, ly = 0.0, lz = -1.0;  // Arah kamera

float l[] = { 0.0, 80.0, 0.0 }; // light source position
float n[] = { 0.0, -40.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };

// fungsi menggambar mobil
void drawCar() {
    // Body utama (pink)
    glPushMatrix();
    glColor3f(1.0, 0.4, 0.6);
    glTranslatef(0, 0.5, 0);  // Posisi mobil
    glScalef(10.0, 2.5, 5.0);  
    glutSolidCube(1.0);
    glPopMatrix();

    // Kabin
    glPushMatrix();
    glColor3f(0.9, 0.3, 0.5);
    glTranslatef(0, 1.5, 0);  // Posisi kabin
    glScalef(3.0, 1.0, 2.0); 
    glutSolidCube(1.0);
    glPopMatrix();

    // Jendela
    glColor3f(0.6, 0.8, 1.0);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(i * 2.5, 1.6, 0);  // Posisi jendela
        glScalef(0.6, 0.8, 1.5);  
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Roda
    glColor3f(1.0, 1.0, 1.0);
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * 4.0, -0.5, j * 2.5);  // Posisi roda
            glRotatef(90, 0, 0, 1);
            glutSolidTorus(0.5, 1.0, 20, 40);  

            // Jari-jari roda
            glColor3f(0.5, 0.5, 0.5);
            for (int k = 0; k < 6; k++) {
                glPushMatrix();
                glRotatef(k * 60, 0, 0, 1);
                glScalef(0.2, 1.0, 0.2); 
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
        glTranslatef(3.0, 1.2, i * 1.5);  // Posisi lampu depan
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.5, 20, 20);  
        glPopMatrix();
    }

    // Lampu belakang
    glColor3f(1.0, 0.0, 0.0);
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(-3.0, 1.2, i * 1.5);  // Posisi lampu belakang
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.5, 20, 20);  
        glPopMatrix();
    }
}

// fungsi untuk proyeksi bayangan
void glShadowProjection(float *l, float *e, float *n) {
    float d, c;
    float mat[16];

    d = n[0] * l[0] + n[1] * l[1] + n[2] * l[2];
    c = e[0] * n[0] + e[1] * n[1] + e[2] * n[2] - d;

    mat[0]  = l[0] * n[0] + c;
    mat[4]  = n[1] * l[0];
    mat[8]  = n[2] * l[0];
    mat[12] = -l[0] * c - l[0] * d;
    mat[1]  = n[0] * l[1];
    mat[5]  = l[1] * n[1] + c;
    mat[9]  = n[2] * l[1];
    mat[13] = -l[1] * c - l[1] * d;
    mat[2]  = n[0] * l[2];
    mat[6]  = n[1] * l[2];
    mat[10] = l[2] * n[2] + c;
    mat[14] = -l[2] * c - l[2] * d;
    mat[3]  = n[0];
    mat[7]  = n[1];
    mat[11] = n[2];
    mat[15] = -d;

    glMultMatrixf(mat); 
}

// fungsi render
void render() {
    glClearColor(0.0, 0.6, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, l);

    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
        glVertex3f(l[0], l[1], l[2]);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-1300.0, e[1] - 0.1, 1300.0);
        glVertex3f(1300.0, e[1] - 0.1, 1300.0);
        glVertex3f(1300.0, e[1] - 0.1, -1300.0);
        glVertex3f(-1300.0, e[1] - 0.1, -1300.0);
    glEnd();

    // gambar mobil
    glPushMatrix();
        glRotatef(ry, 0, 1, 0);
        glRotatef(rx, 1, 0, 0);
        glEnable(GL_LIGHTING);
        drawCar();
    glPopMatrix();

    // gambar bayangan mobil
    glPushMatrix();
        glShadowProjection(l, e, n);
        glRotatef(ry, 0, 1, 0);
        glRotatef(rx, 1, 0, 0);
        glDisable(GL_LIGHTING);
        glColor3f(0.4, 0.4, 0.4); // Warna bayangan
        drawCar();
    glPopMatrix();

    glutSwapBuffers();
}

// fungsi untuk input keyboard
void keypress(unsigned char c, int a, int b) {
    if (c == 27) exit(0);
    else if (c == 's') l[1] -= 5.0;
    else if (c == 'w') l[1] += 5.0;
    else if (c == 'a') l[0] -= 5.0;
    else if (c == 'd') l[0] += 5.0;
    else if (c == 'q') l[2] -= 5.0;
    else if (c == 'e') l[2] += 5.0;
}

// fungsi untuk animasi
void idle() {
    rx += 0.1;
    ry += 0.1;
    render();
}

// fungsi untuk mengubah ukuran window
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 200.0);  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -100.0);  
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 30);
    glutCreateWindow("Proyeksi Bayangan Mobil 3D Cikal");
    glutReshapeFunc(resize);
    glutReshapeWindow(800, 600);
    glutKeyboardFunc(keypress);
    glutDisplayFunc(render);
    glutIdleFunc(idle);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glutMainLoop();
    return 0;
}
