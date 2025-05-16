// library functions for reading .glsl shader files

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include "libs.h"

namespace JShader {

struct Shader {
  GLuint ID;
  std::string vertexSource;
  std::string fragmentSource;
};

struct Character {
  GLuint TextureID;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  GLuint Advance;
};

extern GLuint program;

extern const char *DEFAULT_VERTEX_SHADER;
extern const char *DEFAULT_FRAGMENT_SHADER;

extern const char *current_vertex_source;
extern const char *current_frament_source;

extern GLuint vertexShader;
extern GLuint fragShader;

// initialization functionality //
// - initialize the vbo, vao //
void initialize();

// turn a glsl file into a c string //
char *slurp_file_into_malloced_cstr(const char *file_path);

// turn a glsl c string into a shader and return it //
GLuint createShader(GLenum type, const char *source);

// turn a vertexShader and a fragmentShader into a shader program //
GLuint createShaderProgram(GLuint vertexShader, GLuint framentShader);

} // namespace JShader
