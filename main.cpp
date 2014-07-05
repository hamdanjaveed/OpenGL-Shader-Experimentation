#include <glew.h>
#include <GLUT/glut.h>

void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Shaders");
    glutReshapeFunc(resize);
    glutDisplayFunc(render);

    glutMainLoop();

    return 0;
}
