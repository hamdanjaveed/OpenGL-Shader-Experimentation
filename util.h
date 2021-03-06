#ifndef UTIL_H_GUARD
#define UTIL_H_GUARD

#include <GLFW/glfw3.h>

void loadAndCompileShader(GLuint shaderID, char *const fileName);
GLuint loadPNG(const char *file_name, int *width, int *height);

#endif
