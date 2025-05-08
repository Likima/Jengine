#pragma once

#include "Dependancies/libs.h"

class Renderer
{
public:
    Renderer(GLFWwindow *jw);
    ~Renderer();

    GLuint createShader(GLenum type, const char* source);
    GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint setupGeometry();

    void drawShape(); // TODO define a parameter such that it will draw it
private:
    GLFWwindow *jw;
};