#pragma once

#include "UI_Core/ui_core.h"
#include "game.h"
#include "KeyHandler/KeyHandler.h"

class JEngine {

public:
    JEngine();
    ~JEngine();
private:
    JWindow* jw = nullptr;
    Game* game;
    KeyHandler* kh;
};