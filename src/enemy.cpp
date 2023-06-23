#include "enemy.h"
#include <cmath>
#include <iostream>

int Enemy::getShields() { return _shields; }

int Enemy::getLives() { return _lives; }

void Enemy::updatePosition() {
  position_x -= speed;
  SDL_Rect rect = getRect();
  if (position_x <= (0 - rect.w)) {
    alive = false;
  }
}

void Enemy::takeDamage() {

  _lives -= 1;
  // If lives are 0, set enemy alive to false
  if (_lives <= 0) {
    alive = false;
  }
}

void Enemy::fire(Bullet *b) {
  // Create a bullet and shoot it towards enemies on the right side of the
  // screen
  if (last_fire_time == 0) {
    last_fire_time = SDL_GetTicks();
  }
  unsigned int curr_fire_time = SDL_GetTicks();
  if (curr_fire_time - last_fire_time < fire_cooldown) {
    return;
  }

  // Start the bullet from the enemy ship position
  SDL_Rect rect = getRect();
  b->alive = true;
  b->position_x = position_x;
  b->position_y = position_y;
  b->setDirection(Bullet::Direction::Left);
  b->speed = 1.0f;

  last_fire_time = curr_fire_time;
}
