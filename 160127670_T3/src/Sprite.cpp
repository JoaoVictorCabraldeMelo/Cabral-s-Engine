#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

#include "../include/Resource.hpp"
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

Sprite::Sprite(GameObject &associated) : Component(associated)
{
  this->width = this->associated.box.w;
  this->height = this->associated.box.h;

  this->texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated)
{
  this->texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string file)
{

  SDL_Texture *texture = Resource::GetImage(file);

  this->texture = texture;

  int query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

  if (query != 0)
  {
    std::ofstream logifle("Errors.log", std::ofstream::app);

    logifle << SDL_GetError() << std::endl;

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

void Sprite::Render(float x, float y, float w, float h)
{

  SDL_Rect SpriteOnFrame;

  SpriteOnFrame.h = h;
  SpriteOnFrame.w = w;
  SpriteOnFrame.x = x;
  SpriteOnFrame.y = y;

  const SDL_Rect *dstClip = &SpriteOnFrame;

  int render_flag = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, dstClip);

  if (render_flag != 0)
  {
    std::fstream logfile("Erros.log");

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't Render Copy !!" << std::endl;
    std::cout << "Error Render Copy: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
}

void Sprite::Render(float x, float y)
{
  // cout << "Render Width e Height: " << this->width << " " << this->height << endl;

  this->Render(x, y, this->width, this->height);
}

void Sprite::Render()
{
  this->Render(this->associated.box.x, this->associated.box.y);
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
  // cout << dt << endl;
}

bool Sprite::Is(const string type)
{
  if (type == "Image")
    return true;
  else
    return false;
}