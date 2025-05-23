#include "JWindow.h"

#include <iostream>

#include "Dependancies/libs.h"

JWindow::~JWindow() {
    if(window) glfwDestroyWindow(window);
}

JWindow::JWindow() {
    Initialize();
}

void JWindow::Initialize() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //optional
}

bool JWindow::CreateWindow() {
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    
    window = glfwCreateWindow(mode->width, mode->height, "JEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}