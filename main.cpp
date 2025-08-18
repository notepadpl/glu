//emcc main.cpp -s USE_GLFW=3 -s WASM=1 -o dist/index.html
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>

GLFWwindow* window;

void loop() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f( 0.5, -0.5);
    glVertex2f( 0.0,  0.5);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main() {
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "GLFW + Emscripten", NULL, NULL);
    if (!window) return -1;

    glfwMakeContextCurrent(window);
    emscripten_set_main_loop(loop, 0, 1);

    return 0;
}
