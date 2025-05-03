#include "KeyHandler.h"

#include <iostream>

/*

Devnote: 

KeyHandler has an issue with uc/lc letters. 
issue stems from the fact that say the user clicks 'c'
this passes to @param{key} in key_callback as a GLFW_C
then, using as an index causes it to register as the ascii 'C'

-- I dont think this is an issue. But utilize this as reference for
-- potential bugs.

*/ 

key KeyHandler::ALL_KEYS[128] = {false}; // Definition of the static member
bool KeyHandler::terminate = false;

const char QUIT_KEY = 'Q';

KeyHandler::KeyHandler(GLFWwindow *window)
{
    for (int i = 0; i <= 127; i++)
    {
        ALL_KEYS[i] = {static_cast<char>(i), false};
    }
    terminate = static_cast<bool>(false);
    glfwSetKeyCallback(window, KeyHandler::key_callback);
}

void KeyHandler::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
        ALL_KEYS[key].isPressed = false;
    else
        ALL_KEYS[key].isPressed = true;

    if (ALL_KEYS[QUIT_KEY].isPressed)
        terminate = static_cast<bool>(true);

    // fancy cpp cout
    std::cout << "Key " << ALL_KEYS[key].Character << " was " << ((action == GLFW_RELEASE) ? "released" : "pressed") << std::endl;
}

bool KeyHandler::KeyPressed(const char &c)
{
    if (static_cast<unsigned char>(c) >= 128)
    {
        std::cout << "Character support for character: " << c << " is not yet supported!" << std::endl;
    }
    return (ALL_KEYS[static_cast<unsigned char>(c)].isPressed);
}

bool KeyHandler::isTerminate()
{
    return terminate;
}