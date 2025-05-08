#include "Renderer.h"
#include <iostream>

char *Renderer::vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

char *Renderer::fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main() {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

bool Renderer::initialize()
{
    int width, height;
    glfwGetFramebufferSize(jw, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return true;
}

glm::mat4 Renderer::defineProjection()
{
    int width, height;
    glfwGetFramebufferSize(jw, &width, &height);

    float aspect = static_cast<float>(width) / height;

    if (aspect > 1.0f)
    {
        return glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    }
    else
    {
        float invAspect = 1.0f / aspect;
        return glm::ortho(-1.0f, 1.0f, -invAspect, invAspect, -1.0f, 1.0f);
    }
}
bool Renderer::cleanup(GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader, GLint &posAttrib)
{
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

Renderer::Renderer(GLFWwindow *jw) : jw(jw)
{
    setShaderSource(vertexSource, fragmentSource);
}

Renderer::~Renderer()
{
    setShaderSource(vertexSource, fragmentSource);
}

GLuint Renderer::createShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " shader compilation failed:\n"
                  << infoLog << std::endl;
    }
    return shader;
}

GLuint Renderer::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Shader program linking failed:\n"
                  << infoLog << std::endl;
    }
    return program;
}

GLuint Renderer::setupGeometry(const float *vertices, size_t vertexCount)
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    return vbo;
}

void Renderer::draw(const float *vertices, const int *indices, size_t vertexCount)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    // Create and bind element buffer
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    // Create and set projection matrix
    glm::mat4 projection = defineProjection();
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // Draw using indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(jw);

    // Cleanup
    glDeleteBuffers(1, &ebo);
    cleanup(shaderProgram, vertexShader, fragmentShader, posAttrib);
}
