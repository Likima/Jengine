#pragma once

#include "Dependancies/libs.h"

class Renderer
{
public:
    Renderer(GLFWwindow *jw);
    ~Renderer();

    static void setShaderSource(char *vs, char *fs) {
        vertexSource = vs;
        fragmentSource = fs;
    }

    GLuint createShader(GLenum type, const char* source);
    GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint setupGeometry();

    void draw(const char *vs=nullptr, const char *fs=nullptr); // TODO define a parameter such that it will draw it
private:
    GLFWwindow *jw;

    static char *vertexSource;

    static char *fragmentSource;
};