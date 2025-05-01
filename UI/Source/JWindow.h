#pragma once

#include <GLFW/glfw3.h>

class JWindow {
public:
    JWindow();
    ~JWindow();
    
    bool CreateWindow();
private:
    GLFWwindow* window = nullptr;
    void Initialize();
};