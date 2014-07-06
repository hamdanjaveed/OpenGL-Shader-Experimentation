#include <string>
#include <fstream>
#include "util.h"

// loads a file and returns a string
std::string loadFile(const char *const fileName) {
    std::ifstream file(fileName);
    std::string text;

    while (file.good()) {
        std::string line;
        std::getline(file, line);
        text.append(line + "\n");
    }

    return text;
}

// load the shader from a file and bind it to the given ID
void loadAndCompileShader(GLuint shaderID, char *const fileName) {
    const std::string shaderSource = loadFile(fileName);

    const GLchar *cShaderSource = shaderSource.c_str();
    const GLint cShaderSize = shaderSource.size();

    glShaderSource(shaderID, 1, &cShaderSource, &cShaderSize);
    glCompileShader(shaderID);
}
