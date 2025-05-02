#pragma once
#include <GLFW/glfw3.h>

struct key {
    char Character;
    bool isPressed;
};

class KeyHandler {
public:
    KeyHandler(GLFWwindow* window);
    ~KeyHandler() = default;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool KeyPressed(char &c);
private:
    static key ALL_KEYS[128];
};