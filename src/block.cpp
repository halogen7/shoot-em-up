#include "block.h"
#include <cmath>
#include <iostream>

SDL_Rect Block::getRect() {
  SDL_Rect rect;
  rect.w = _width * size;
  rect.h = _height * size;

  rect.x = position_x * _width;
  rect.y = position_y * _height;

  return rect;
}

bool Block::isCollision(SDL_Rect b) {
  SDL_Rect rect = getRect();
  return SDL_HasIntersection(&b, &rect);
}
