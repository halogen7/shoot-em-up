#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Player player, std::vector<Enemy *> enemies,
              std::vector<Bullet *> enemyBullets);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif