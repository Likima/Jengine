#include "KeyHandler.h"

#include <iostream>

key KeyHandler::ALL_KEYS[128] = {false}; // Definition of the static member

KeyHandler::KeyHandler(GLFWwindow* window) {
    for(int i = 0; i <= 127; i++) {
        ALL_KEYS[i] = {static_cast<char>(i), false};
    }
    glfwSetKeyCallback(window, KeyHandler::key_callback);
}

void KeyHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE) ALL_KEYS[key].isPressed = false;
    else ALL_KEYS[key].isPressed = true;

    //fancy cpp cout
    std::cout<<"Key "<<ALL_KEYS[key].Character<<" was " <<
        ((action == GLFW_RELEASE) ? "released" : "pressed")<< std::endl;
}

bool KeyHandler::KeyPressed(char &c) {
    if(c>=128) {
        std::cout<<"Character support for character: " << c << " is not yet supported!" <<std::endl;
    }
    return(ALL_KEYS[c].isPressed);
}