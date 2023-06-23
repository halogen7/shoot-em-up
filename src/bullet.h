#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "block.h"

class Bullet : public Block {
public:
  using Block::Block;
  enum class Direction { Left, Right };

  void updatePosition();
  void setDirection(Direction d);
  void getPosition();

  float speed{2.0f};
  int size{1};
  bool alive{false};
  Direction dir;
};

#endif