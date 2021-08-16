#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include "../lib/Sprite.hpp"
#include "../lib/Game.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../lib/SDL_include.h"

Sprite::Sprite()
{
  std::cout << "Image not loaded" << std::endl;
  return nullptr;
}

Sprite::Sprite(std::string file)
{
  this->texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite()
{
  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
  }
}

void Sprite::Open(std::string file)
{

  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
  }

  SDL_Renderer *renderer = Game::GetRenderer();

  SDL_Texture *texture = IMG_LoadTexture(renderer, file);

  if (texture == nullptr)
  {
    std::ofstream logfile("Errors.log");

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't Load Texture !!" << std::endl;
    std::cout << "Error Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  int query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

  if (query != 0)
  {
    std::ofstream logifle("Errors.log");

    logifle << SDL_GetError() << std::endl;

    logifle.close();

    std::cout << "Couldn't load Query Texture !! " << std::endl;
    std::cout << "Error Query Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  Sprite::SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int h, int w)
{
  this->clipRect.h = h;
  this->clipRect.w = w;
  this->clipRect.x = x;
  this->clipRect.y = y;
}

void Sprite::Render(int x, int y)
{

  SDL_Renderer *renderer = Game::GetRenderer();

  SDL_Rect dstClip;

  dstClip.h = this->clipRect.h;
  dstClip.w = this->clipRect.w;
  dstClip.x = x;
  dstClip.y = y;

  int render_flag = SDL_RenderCopy(renderer, this->texture, this->clipRect, dstClip);
}

bool Sprite::IsOpen()
{
  if (this->texture != nullptr)
  {
    return true;
  }
  return false;
}
