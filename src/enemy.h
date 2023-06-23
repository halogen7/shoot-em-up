#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "block.h"
#include "bullet.h"
#include <vector>

class Enemy : public Block {
public:
  using Block::Block;

  void takeDamage();
  int getShields();
  int getLives();

  void updatePosition();
  void fire(Bullet *b);

  float speed{0.25f};
  bool alive{false};

private:
  const unsigned int fire_cooldown{2000};
  unsigned int last_fire_time{0};

  const int max_shields{0};
  const int max_lives{1};

  int _shields = max_shields;
  int _lives = max_lives;
};

#endif