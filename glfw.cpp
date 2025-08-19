#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>

GLuint car;
float carrot = 0.0f;
GLFWwindow* window;

void loadObj(const char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;

    car = glGenLists(1);
    fp = fopen(fname, "r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(car, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POINTS);
        while (!(feof(fp)))
        {
            read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
            if (read == 4 && ch == 'v')
            {
                glVertex3f(x, y, z);
            }
        }
        glEnd();
        glPopMatrix();
    }
    glEndList();
    fclose(fp);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

void drawCar()
{
    glPushMatrix();

    glColor3f(1.0f, 0.23f, 0.27f);
    glTranslatef(0.0f, -0.9f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    glRotatef(carrot, 0, 1, 0);
    glCallList(car);
    glPopMatrix();

    carrot += 0.6f;
    if (carrot > 360) carrot -= 360;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    reshape(width, height);
}

void main_loop()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawCar();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(int argc, char **argv)
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Prosta konfiguracja okna OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(1000, 750, "ObjLoader", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    loadObj("tee.obj");

    // ustaw początkowy viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    reshape(width, height);

    // zamiast while loop używamy emscripten_set_main_loop
    emscripten_set_main_loop(main_loop, 0, 1);

    return 0;
}
