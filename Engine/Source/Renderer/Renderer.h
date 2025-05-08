#pragma once

#include "Dependancies/libs.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    glm::mat4 normalizeProjection();

    void draw(const float *vertices, const int *indices, size_t vertexCount); 

    void initialize();
    void cleanup(GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader, GLint &posAttrib);
protected:
    GLFWwindow *jw;
    GLuint vbo;
    GLuint vao;

    static char *vertexSource;
    static char *fragmentSource;
};