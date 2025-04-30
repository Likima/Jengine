#pragma once

#include <GLFW/glfw3.h>

class JWindow {
public:
    JWindow();

private:
    GLFWwindow* Window;
    bool Initialize();
};