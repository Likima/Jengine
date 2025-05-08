#include "Renderer.h"
#include <iostream>

char* Renderer::vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

char* Renderer::fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main() {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

bool Renderer::initialize() {
    int width, height;
    glfwGetFramebufferSize(jw, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return true;
}

bool Renderer::cleanup(GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader, GLint &posAttrib) {
    glDisableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

Renderer::Renderer(GLFWwindow *jw) : jw(jw) {
    setShaderSource(vertexSource, fragmentSource);
}

Renderer::~Renderer() {
    setShaderSource(vertexSource, fragmentSource);
}

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

GLuint Renderer::setupGeometry(const float* vertices, size_t vertexCount) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    return vbo;
}

void Renderer::draw(const float *vertices, size_t vertexCount) {

    // example
    // float vertices[] = {
    //     -0.5f, -0.5f,
    //      0.5f, -0.5f,
    //      0.0f,  0.5f
    // };

    vbo = setupGeometry(vertices, vertexCount);

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(jw);
    cleanup(shaderProgram, vertexShader, fragmentShader, posAttrib);
}
