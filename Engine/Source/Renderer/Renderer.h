#pragma once

#include "Dependancies/libs.h"

class Renderer
{
public:
    Renderer(GLFWwindow *jw);
    ~Renderer();

    static void setShaderSource(char *vs, char *fs)
    {
        vertexSource = vs;
        fragmentSource = fs;
    }

    GLuint createShader(GLenum type, const char *source);
    GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint setupGeometry(const float *vertices, size_t vertexCount);

    void draw(const float *vertices, const int *indices, size_t vertexCount); // TODO define a parameter such that it will draw it

    bool initialize();
    bool cleanup(GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader, GLint &posAttrib);
protected:
    GLFWwindow *jw;
    GLuint vbo;
    GLuint vao;

    static char *vertexSource;

    static char *fragmentSource;
};