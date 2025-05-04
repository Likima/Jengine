#pragma once
#include "Dependancies/libs.h"

struct key {
    char Character;
    bool isPressed;
};

class KeyHandler {
public:
    KeyHandler(GLFWwindow* window);
    ~KeyHandler() = default;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool KeyPressed(const char &c);
    static bool isTerminate();
    
private:
    static key ALL_KEYS[128];
    static bool terminate;
};