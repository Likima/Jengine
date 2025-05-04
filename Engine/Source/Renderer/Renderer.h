#pragma once

#include "Dependancies/libs.h"

class Renderer
{
public:
    Renderer(GLFWwindow *jw);
    ~Renderer();

    void drawShape(); // TODO define a parameter such that it will draw it
private:
    GLFWwindow *jw;
};