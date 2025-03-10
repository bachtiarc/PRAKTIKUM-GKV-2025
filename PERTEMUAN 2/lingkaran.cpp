// NAMA : CIKAL WAHYUNING BACHTIAR
// NIM : 24060123140175
// LAB : B1

// TUGAS PRAKTIKUM 2

#include <GLUT/glut.h>
#include <cmath>

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Background hitam
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.4, 0.7); // Warna pink

    glBegin(GL_POLYGON);
    int numSegments = 100;
    float radius = 0.5f;
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Lingkaran Pink");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
