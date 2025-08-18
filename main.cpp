#include <GL/glut.h>
#include <emscripten/emscripten.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("FreeGLUT with Emscripten Loop");
    glutDisplayFunc(display);

    // Używamy pętli Emscripten zamiast glutMainLoop()
    emscripten_set_main_loop(display, 0, 1);

    return 0;
}
