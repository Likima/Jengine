// library functions for reading .glsl shader files

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

namespace JShader
{
    struct Shader
    {
        GLuint ID;
        std::string vertexSource;
        std::string fragmentSource;
    };

    extern const char *DEFAULT_VERTEX_SHADER;
    extern const char *DEFAULT_FRAGMENT_SHADER;

    char *slurp_file_into_malloced_cstr(const char *file_path);
    bool compileShaderFromSource(const GLchar *source, GLenum type, GLuint *shader);
    bool compileShader(const char *filePath, GLenum type, GLuint *shader);
    bool createShaderProgram(GLuint vert_shader, GLuint frag_shader, GLuint *program);
    bool loadShaderFromFile(const char *shaderName, GLenum type, GLuint *shader);

    void DeleteShader(GLuint shader);

}