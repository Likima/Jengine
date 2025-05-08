#include "Renderer.h"
#include <iostream>

const char *vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

const char *fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main() {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

Renderer::Renderer(GLFWwindow *jw) : jw(jw) {}
Renderer::~Renderer() {}

GLuint Renderer::createShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") 
                  << " shader compilation failed:\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint Renderer::createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
    }
    return program;
}

GLuint Renderer::setupGeometry() {
    const float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    return vbo;
}

void Renderer::drawShape() {
    int width, height;
    glfwGetFramebufferSize(jw, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo = setupGeometry();

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(jw);

    glDisableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
