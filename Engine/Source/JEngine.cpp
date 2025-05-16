/*
 * Credit to https://gist.github.com/mariobadr/673bbd5545242fcf9482 for game
 * loop logic
 */

#include "JEngine.h"
#include "Game_Core/game_core.h"

#include <chrono>
#include <iostream>

int SCREEN_HEIGHT = 600;
int SCREEN_WIDTH = 900;

// std::string JEngine::rootPath = "";

JEngine::~JEngine() {
  delete jw;
  delete game;
  delete renderer;
}

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms);

void JEngine::onStart() {
  game->onStart();
  for (auto &e : game->getEntityList())
    e->onStart();
}

bool JEngine::handle_events() {
  return kh->isTerminate(); // true if the user wants to quit the game
}

void JEngine::update(game_state *gs) { game->update(); }

void JEngine::render(game_state const &gs) { game->render(); }

game_state JEngine::interpolate(game_state const &current,
                                game_state const &previous, float alpha) {
  game_state interpolated_state;

  // interpolate between previous and current by alpha here

  return interpolated_state;
}

JEngine::JEngine() {

  // setRootPath(PROJECT_ROOT);

  game = Game_Core::getGame();

  std::cout << "JEngine successfully initialized!" << std::endl;
  jw = UI_Core::CreateJWindow();
  jw->CreateWindow();

  this->kh = new KeyHandler(jw->getWindow());
  this->renderer = new Renderer(jw->getWindow());

  game->attachKeyHandler(kh);
  game->attachWindow(jw->getWindow());

  glfwGetFramebufferSize(jw->getWindow(), &SCREEN_WIDTH, &SCREEN_HEIGHT);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, true);

  glfwMakeContextCurrent(jw->getWindow());

  load_gl_extensions();

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return;
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
  }

  using clock = std::chrono::high_resolution_clock;

  std::chrono::nanoseconds lag(0ns);
  auto time_start = clock::now();
  bool terminate = false;

  game_state current_state;
  game_state previous_state;

  onStart();

  while (!terminate) {
    glfwPollEvents(); // key input

    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

    terminate = handle_events();

    while (lag >= timestep) {
      lag -= timestep;

      previous_state = current_state;
      update(&current_state);
    }

    auto alpha = (float)lag.count() / timestep.count();
    auto interpolated_state = interpolate(current_state, previous_state, alpha);

    render(interpolated_state);
  }

  std::cout << "Thank you for using JEngine!" << std::endl;
}
