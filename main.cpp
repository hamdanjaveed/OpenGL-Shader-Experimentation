#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "util.h"

using namespace std;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // initialize glew
    glewExperimental = GL_TRUE;
    glewInit(); glGetError(); // this is to get rid of the 1280 error caused by glewInit()

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    const GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f, 1.0f, // top left
        0.5f,  0.5f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f  // bottom left
    };

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    loadAndCompileShader(vertexShader, (char *)"vertexShader.vsh");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    loadAndCompileShader(fragmentShader, (char *)"fragmentShader.fsh");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint positionAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(positionAttrib);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "textureCoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    GLuint texture;
    glGenTextures(1, &texture);
    int width;
    int height;
    texture = loadPNG("niccage.png", &width, &height);

    GLint widthUniform = glGetUniformLocation(shaderProgram, "width");
    glUniform1i(widthUniform, width);

    GLint heightUniform = glGetUniformLocation(shaderProgram, "height");
    glUniform1i(heightUniform, height);

    GLint err;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &err);
    cout << "  Vertex shader : " << ((err == GL_TRUE) ? "OK" : "ERROR") << endl;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &err);
    cout << "Fragment shader : " << ((err == GL_TRUE) ? "OK" : "ERROR") << endl;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &err);
    cout << " Program Linked : " << ((err == GL_TRUE) ? "OK" : "ERROR") << endl;
    GLenum genErr = glGetError();
    cout << "  General Error : " << ((genErr != GL_NO_ERROR) ? "ERROR - " : "OK");
    if (genErr != GL_NO_ERROR) cout << genErr;
    cout << endl;

    // main loop
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteBuffers(1, &elementBufferObject);
    glDeleteBuffers(1, &vertexBufferObject);

    glDeleteVertexArrays(1, &vertexArrayObject);

    glfwTerminate();
    return 0;
}

