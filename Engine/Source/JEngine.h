#pragma once

#include "Entities/Entity.hpp"
#include "KeyHandler/KeyHandler.h"
#include "Renderer/Renderer.h"
#include "UI_Core/ui_core.h"
#include "game.h"

struct game_state {
  // this contains the state of your game, such as positions and velocities
};

class JEngine {

public:
  JEngine();
  ~JEngine();
  bool terminate = false;

  // static void setRootPath(const std::string& path) { rootPath = path; }
  static std::string getRootPath() { return rootPath; }
  static std::string getShaderPath() { return rootPath + "/Assets/Shaders/"; }

private:
  JWindow *jw = nullptr;
  Game *game;
  KeyHandler *kh;
  Renderer *renderer;

  static std::string rootPath;

  game_state interpolate(game_state const &current, game_state const &previous,
                         float alpha);
  void update(game_state *gs);
  void render(game_state const &gs);
  void onStart();
  bool handle_events();
};
