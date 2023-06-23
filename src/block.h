#ifndef BLOCK_H
#define BLOCK_H

#include "SDL.h"
#include <vector>

class Block {
public:
  Block(int size, int grid_width, int grid_height, int width, int height,
        float x, float y)
      : size(size), _grid_width(grid_width), _grid_height(grid_height),
        _width(width), _height(height), position_x(x), position_y(y) {}

  SDL_Rect getRect();
  bool isCollision(SDL_Rect b);

  float position_x;
  float position_y;
  int size;

protected:
  int _width;
  int _height;

  int _grid_width;
  int _grid_height;
};

#endif