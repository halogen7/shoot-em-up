#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "block.h"
#include "bullet.h"
#include "controller.h"
#include "enemy.h"
#include "player.h"
#include "renderer.h"

#include <queue>
#include <random>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height,
       std::size_t screen_width, std::size_t screen_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  bool CheckPlayerCollision(Bullet *b);
  bool CheckPlayerCollision(Enemy *e);
  void SpawnEnemy();
  void Load();
  Bullet *SpawnBullet();

  ~Game() {
    for (auto e : _enemies) {
      delete e;
    }

    for (auto b : _enemyBullets) {
      delete b;
    }
  }

private:
  Player _player;
  int grid_height;
  int grid_width;
  int screen_width;
  int screen_height;
  std::vector<Enemy *> _enemies;
  std::vector<Bullet *> _enemyBullets;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  static const size_t MAX_ENEMIES{50};
  static const size_t MAX_BULLETS{100};

  static const unsigned int spawn_enemy_cooldown{400};
  unsigned int last_enemy_spawn_time{0};

  int score{0};
  void Update();
};

#endif