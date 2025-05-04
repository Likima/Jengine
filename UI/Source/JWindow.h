#pragma once

#include "Dependancies/libs.h"

class JWindow {
public:
    JWindow();
    ~JWindow();
    
    bool CreateWindow();

    GLFWwindow* getWindow() { return window; }
private:
    GLFWwindow* window = nullptr;
    void Initialize();
};