#include "bullet.h"
#include <cmath>
#include <iostream>

void Bullet::setDirection(Direction d) { dir = d; }

void Bullet::updatePosition() {

  if (dir == Direction::Right) {
    position_x += speed;
  } else if (dir == Direction::Left) {
    position_x -= speed;
  }

  if (position_x < -1 || position_x > _grid_width) {
    alive = false;
  }
}

void Bullet::getPosition() {
  std::cout << "X: " << position_x << " "
            << "Y: " << position_y << std::endl;
}