#include "ShaderLib.h"
#include "Dependancies/libs.h"
#include <iostream>

namespace JShader {
const char *DEFAULT_VERTEX_SHADER = R"glsl(
        #version 330 core
        layout (location = 0) in vec2 position;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * vec4(position, 0.0, 1.0);
        }
    )glsl";

const char *DEFAULT_FRAGMENT_SHADER = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )glsl";

GLuint VAO = 0;
GLuint VBO = 0;

GLuint vertexShader = 0;
GLuint fragShader = 0;

GLuint program = 0;

char *slurp_file_into_malloced_cstr(const char *file_path) {
  FILE *f = NULL;
  char *buffer = NULL;
  long size = 0;

  f = fopen(file_path, "r");
  if (f == NULL)
    goto fail;
  if (fseek(f, 0, SEEK_END) < 0)
    goto fail;

  size = ftell(f);
  if (size < 0)
    goto fail;

  buffer = (char *)malloc(size + 1);
  if (buffer == NULL)
    goto fail;

  if (fseek(f, 0, SEEK_SET) < 0)
    goto fail;

  fread(buffer, 1, size, f);
  if (ferror(f))
    goto fail;

  buffer[size] = '\0';

  if (f) {
    fclose(f);
    errno = 0;
  }
  return buffer;

fail:
  if (f) {
    int saved_errno = errno;
    fclose(f);
    errno = saved_errno;
  }
  if (buffer)
    free(buffer);
  return NULL;
}

// initialization functionality //
// - initialize the vbo, vao //
void initialize() {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
}

// turn a glsl c string into a shader and return it //
GLuint createShader(GLenum type, const char *source) {

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
              << " shader compilation failed:\n"
              << infoLog << std::endl;
  }

  else {
    if (type == GL_VERTEX_SHADER) {
      vertexShader = shader;
    } else if (type == GL_FRAGMENT_SHADER) {
      fragShader = shader;
    } else {
      std::cout << "Unrecognized shader!" << std::endl;
    }
  }

  return shader;
}

// turn a vertexShader and a fragmentShader into a shader program //

GLuint createShaderProgram(GLuint vs, GLuint fs) {
  program = glCreateProgram();
  vertexShader = vs;
  fragShader = fs;

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cout << "Shader program linking failed: \n" << infoLog << std::endl;
  }

  return program;
}
} // namespace JShader

