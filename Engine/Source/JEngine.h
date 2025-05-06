#pragma once

#include "UI_Core/ui_core.h"
#include "game.h"
#include "KeyHandler/KeyHandler.h"
#include "Renderer/Renderer.h"

struct game_state {
    // this contains the state of your game, such as positions and velocities
};

class JEngine {

public:
    JEngine();
    ~JEngine();
    bool terminate = false;
private:
    JWindow* jw = nullptr;
    Game* game;
    KeyHandler* kh;
    Renderer* renderer;

    game_state interpolate(game_state const & current, game_state const & previous, float alpha);
    void update(game_state * gs);
    void render(game_state const &gs);
    void onStart();
    bool handle_events();
};