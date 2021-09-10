#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Component.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

using namespace std;

Sprite::Sprite() : Component()
{
  this->width = this->associated.box.w;
  this->height = this->associated.box.h;
  this->texture = nullptr;
}

Sprite::Sprite(string file) : Component()
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

  SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

  if (texture == nullptr)
  {
    std::ofstream logfile("Errors.log");

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't Load Texture !!" << std::endl;
    std::cout << "Error Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  this->texture = texture;

  int query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

  if (query != 0)
  {
    std::ofstream logifle("Errors.log");

    logifle << SDL_GetError() << std::endl;

    logifle.close();

    std::cout << "Couldn't load Query Texture !!" << std::endl;
    std::cout << "Error Query Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  Sprite::SetClip(0, 0, this->height, this->width);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.h = h;
  this->clipRect.w = w;
}

void Sprite::Render()
{

  SDL_Rect SpriteOnFrame;

  SpriteOnFrame.h = Game::GetInstance().GetHeight();
  SpriteOnFrame.w = Game::GetInstance().GetWidth();
  SpriteOnFrame.x = 0;
  SpriteOnFrame.y = 0;

  const SDL_Rect *dstClip = &SpriteOnFrame;

  int render_flag = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, dstClip);

  if (render_flag != 0)
  {
    std::fstream logfile("Erros.log");

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't Render Copy !!" << std::endl;
    std::cout << "Error Render Copy: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
}

bool Sprite::IsOpen()
{
  if (this->texture != nullptr)
  {
    return true;
  }
  return false;
}

void Sprite::Update(float dt)
{
  cout << dt << endl;
}

bool Sprite::Is(const string type)
{
  if (type == "Image")
    return true;
  else
    return false;
}