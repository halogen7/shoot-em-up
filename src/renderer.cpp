#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Space Shooter Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player player, std::vector<Enemy *> enemies,
                      std::vector<Bullet *> enemyBullets) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 255);
  SDL_RenderClear(sdl_renderer);

  // Render player bullets
  SDL_SetRenderDrawColor(sdl_renderer, 255, 204, 0, 255);
  for (Bullet &b : player.bullets) {
    if (b.alive) {
      SDL_Rect pbullet = b.getRect();
      SDL_RenderFillRect(sdl_renderer, &pbullet);
    }
  }

  // Render player ship
  if (!player.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  } else {
    switch (player.getLives()) {
    case 3:
      SDL_SetRenderDrawColor(sdl_renderer, 0, 122, 204, SDL_ALPHA_OPAQUE);
      break;
    case 2:
      SDL_SetRenderDrawColor(sdl_renderer, 7, 173, 104, SDL_ALPHA_OPAQUE);
      break;
    case 1:
      SDL_SetRenderDrawColor(sdl_renderer, 207, 191, 17, SDL_ALPHA_OPAQUE);
      break;
    }
    SDL_Rect playerRect = player.getRect();
    SDL_RenderFillRect(sdl_renderer, &playerRect);

    if (player.shielded) {
      SDL_SetRenderDrawColor(sdl_renderer, 91, 252, 247, SDL_ALPHA_TRANSPARENT);
      SDL_Rect shieldRect = player.getShieldRect();
      SDL_RenderFillRect(sdl_renderer, &shieldRect);
    }
  }

  // Render enemy ship
  for (auto e : enemies) {
    if (e->alive) {
      SDL_Rect enemyRect = e->getRect();
      SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
      /* if (!e->alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
      } */
      SDL_RenderFillRect(sdl_renderer, &enemyRect);
    }
  }

  // Render enemy bullets
  SDL_SetRenderDrawColor(sdl_renderer, 0, 204, 0, 255);
  for (auto b : enemyBullets) {
    if (b->alive) {
      SDL_Rect bRect = b->getRect();
      SDL_RenderFillRect(sdl_renderer, &bRect);
    }
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
