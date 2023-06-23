#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           std::size_t screen_width, std::size_t screen_height)
    : _player(1, grid_width, grid_height, screen_width / grid_width,
              screen_height / grid_height, grid_width * 0.2 / 2,
              grid_height / 2),
      engine(dev()), grid_height(grid_height), grid_width(grid_width),
      screen_width(screen_width), screen_height(screen_height),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  _enemies.reserve(MAX_ENEMIES);
  _enemyBullets.reserve(MAX_BULLETS);
  Load();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _player);
    Update();
    renderer.Render(_player, _enemies, _enemyBullets);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (!_player.alive)
    return;

  _player.Update();

  unsigned int curr_enemy_spawn_time = SDL_GetTicks();
  if (curr_enemy_spawn_time - last_enemy_spawn_time >= spawn_enemy_cooldown) {
    SpawnEnemy();
    last_enemy_spawn_time = curr_enemy_spawn_time;
  }

  for (auto e : _enemies) {
    if (e->alive) {
      for (Bullet &b : _player.bullets) {
        if (b.alive) {
          SDL_Rect bulletRect = b.getRect();
          SDL_Rect enemyRect = e->getRect();
          if (SDL_HasIntersection(&bulletRect, &enemyRect)) {
            e->takeDamage();
            b.alive = false;
            score++;
          }
        }
      }
      if (CheckPlayerCollision(e)) {
        e->takeDamage();
        if (!_player.shielded) {
          _player.takeDamage();
        }
      } else {
        e->updatePosition();
        auto b = SpawnBullet();
        if (b) {
          e->fire(b);
        }
      }
    }
  }

  if (_player.alive) {
    for (auto b : _enemyBullets) {
      if (b->alive) {
        if (CheckPlayerCollision(b)) {
          b->alive = false;
          if (!_player.shielded) {
            _player.takeDamage();
          }
        } else {
          b->updatePosition();
        }
      }
    }
  }
}

bool Game::CheckPlayerCollision(Enemy *e) {

  SDL_Rect playerRect = _player.getRect();
  if (_player.shielded) {
    playerRect = _player.getShieldRect();
  }
  return e->isCollision(playerRect);
}

bool Game::CheckPlayerCollision(Bullet *b) {

  SDL_Rect playerRect = _player.getRect();
  if (_player.shielded) {
    playerRect = _player.getShieldRect();
  }
  return b->isCollision(playerRect);
}

int Game::GetScore() const { return score; }

void Game::Load() {
  int x = grid_width;
  int y = 0;
  for (auto i = 0; i < _enemies.capacity(); i++) {
    _enemies.emplace_back(new Enemy(2, grid_width, grid_height,
                                    (screen_width / grid_width),
                                    (screen_height / grid_height), x, y));
  }

  for (auto i = 0; i < _enemyBullets.capacity(); i++) {
    _enemyBullets.emplace_back(new Bullet(1, grid_width, grid_height,
                                          (screen_width / grid_width),
                                          (screen_height / grid_height), x, y));
  }
}
void Game::SpawnEnemy() {
  for (auto e : _enemies) {
    if (!e->alive) {
      int y = random_h(engine);
      e->position_x = grid_width;
      e->position_y = y;
      e->alive = true;
      break;
    }
  }
}

Bullet *Game::SpawnBullet() {
  for (auto b : _enemyBullets) {
    if (!b->alive) {
      return b;
    }
  }
  return nullptr;
}