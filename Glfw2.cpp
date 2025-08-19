#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct Vertex {
    float x, y, z;
};

std::vector<Vertex> vertices;
GLuint carrot = 0;
GLFWwindow* window;

void loadObj(const char *fname)
{
    FILE *fp;
    int read;
    float x, y, z;
    char ch;

    fp = fopen(fname, "r");
    if (!fp)
    {
        printf("Can't open file %s\n", fname);
        exit(1);
    }

    vertices.clear();
    while (!feof(fp))
    {
        read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
        if (read == 4 && ch == 'v')
        {
            vertices.push_back({x, y, z});
        }
    }
    fclose(fp);

    printf("Wczytano %zu wierzchołków z pliku: %s\n", vertices.size(), fname);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);  // Projekcja perspektywiczna

    glMatrixMode(GL_MODELVIEW);
}

void drawCar()
{
    glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    glRotatef((float)carrot, 0, 1, 0);

    glBegin(GL_POINTS);
    for (const auto& v : vertices)
    {
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();

    glPopMatrix();

    carrot += 1;
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
    glTranslatef(0.0f, 0.0f, -10.0f);  // Odsunięcie kamery w tył

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

    glEnable(GL_DEPTH_TEST);  // <- Włączenie testu głębokości

    loadObj("asserts/tee.obj");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    reshape(width, height);

    emscripten_set_main_loop(main_loop, 0, 1);

    return 0;
}
