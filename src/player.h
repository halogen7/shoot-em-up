#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "block.h"
#include "bullet.h"
#include <vector>

class Player : public Block {
public:
  using Block::Block;
  enum class Direction { kUp, kDown, kLeft, kRight, none };

  void Update();
  void deployShield();
  void takeDamage();
  int getShields();
  int getLives();
  void fire();

  SDL_Rect getShieldRect();

  Direction direction = Direction::none;

  float speed{1.0f};
  bool alive{true};
  bool shielded{false};
  std::vector<Bullet> bullets;

  int shield_offset{20};
  int shield_size{4};

private:
  void updatePosition();

  const int max_shields{3};
  const int max_lives{3};

  const unsigned int fire_cooldown{200};
  unsigned int last_fire_time{0};

  const unsigned int shield_cooldown{10000};
  const unsigned int shield_timer{5000};
  unsigned int last_shield_time{0};

  int _shields = max_shields;
  int _lives = max_lives;
};

#endif