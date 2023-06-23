#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

#include "SDL.h"

int SDL_main(int argc, char *argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{720};
  constexpr std::size_t kScreenHeight{480};
  constexpr std::size_t kGridWidth{72};
  constexpr std::size_t kGridHeight{48};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, kScreenWidth, kScreenHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}
