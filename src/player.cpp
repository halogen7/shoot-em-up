#include "player.h"
#include <cmath>
#include <iostream>

int Player::getShields() { return _shields; }

int Player::getLives() { return _lives; }

void Player::Update() {
  if (shielded) {
    unsigned int curr_shield_time = SDL_GetTicks();
    if (curr_shield_time - last_shield_time > shield_timer) {
      shielded = false;
    }
  }

  updatePosition();
}

void Player::updatePosition() {
  switch (direction) {
  case Direction::kUp:
    position_y -= speed;
    break;

  case Direction::kDown:
    position_y += speed;
    break;

  case Direction::kLeft:
    if (0 < position_x - speed) {
      position_x -= speed;
    }
    break;

  case Direction::kRight:
    if (position_x + speed < _grid_width * 0.2) {
      position_x += speed;
    }
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  position_y = fmod(position_y + _grid_height, _grid_height);
  for (Bullet &b : bullets) {
    b.updatePosition();
  }
}

void Player::takeDamage() {

  _lives -= 1;

  // If lives are 0, set player alive to false
  if (_lives <= 0) {
    alive = false;
  }
}

void Player::deployShield() {
  if (_shields > 0) {
    unsigned int curr_shield_time = SDL_GetTicks();
    if (!last_shield_time == 0 &&
        curr_shield_time - last_shield_time < shield_cooldown) {
      return;
    }
    _shields -= 1;
    shielded = true;
    last_shield_time = curr_shield_time;
  }
}

void Player::fire() {
  // Create a bullet and shoot it towards enemies on the right side of the
  // screen
  unsigned int curr_fire_time = SDL_GetTicks();
  if (curr_fire_time - last_fire_time < fire_cooldown) {
    return;
  }

  // Start the bullet from the player ship position
  Bullet b(1, _grid_width, _grid_height, _width, _height, position_x,
           position_y);
  b.setDirection(Bullet::Direction::Right);
  b.alive = true;

  // Give bullet to the bullet handler
  bullets.push_back(b);

  last_fire_time = curr_fire_time;
}

SDL_Rect Player::getShieldRect() {
  SDL_Rect rect = getRect();
  rect.y += rect.h / 2;
  rect.h *= shield_size;
  rect.x += shield_offset;
  rect.y -= rect.h / 2;
  return rect;
}
