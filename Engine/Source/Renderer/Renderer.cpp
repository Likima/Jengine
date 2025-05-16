#include "Renderer.h"
#include "Dependancies/ShaderLib.h"
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

void Renderer::initialize() {
  int width, height;
  glfwGetFramebufferSize(jw, &width, &height);
  glViewport(0, 0, width, height);

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // initialize the shader objects (vao, vbo)
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

glm::mat4 Renderer::normalizeProjection() {
  int width, height;
  glfwGetFramebufferSize(jw, &width, &height);

  float aspect = static_cast<float>(width) / height;

  if (aspect > 1.0f) {
    return glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
  } else {
    float invAspect = 1.0f / aspect;
    return glm::ortho(-1.0f, 1.0f, -invAspect, invAspect, -1.0f, 1.0f);
  }
}

void Renderer::cleanup(GLuint &shaderProgram, GLuint &vertexShader,
                       GLuint &fragmentShader, GLint &posAttrib) {
  glDisableVertexAttribArray(posAttrib);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Renderer::Renderer(GLFWwindow *jw) : jw(jw) {
  setShaderSource(vertexSource, fragmentSource);
}

Renderer::~Renderer() { setShaderSource(vertexSource, fragmentSource); }

// @deprecated
GLuint Renderer::createShader(GLenum type, const char *source) {
  return JShader::createShader(type, source);
}

// @deprecated
GLuint Renderer::createShaderProgram(GLuint vertexShader,
                                     GLuint fragmentShader) {
  return JShader::createShaderProgram(vertexShader, fragmentShader);
}

GLuint Renderer::setupGeometry(const float *vertices, size_t vertexCount) {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices,
               GL_STATIC_DRAW);
  return vbo;
}

void Renderer::draw(const float *vertices, const int *indices,
                    size_t vertexCount) {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices,
               GL_STATIC_DRAW);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices,
               GL_STATIC_DRAW);

  JShader::createShader(GL_VERTEX_SHADER, vertexSource);
  JShader::createShader(GL_FRAGMENT_SHADER, fragmentSource);
  JShader::createShaderProgram(JShader::vertexShader, JShader::fragShader);

  glUseProgram(JShader::program);

  glm::mat4 projection = normalizeProjection();
  GLint projectionLoc = glGetUniformLocation(JShader::program, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  GLint posAttrib = glGetAttribLocation(JShader::program, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(jw);

  glDeleteBuffers(1, &ebo);
  cleanup(JShader::program, JShader::vertexShader, JShader::fragShader,
          posAttrib);
}
