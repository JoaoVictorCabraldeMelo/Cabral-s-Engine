#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

#include "../include/Resource.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Component.hpp"
#include "../include/Camera.hpp"
#include "../include/Rect.hpp"

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
  this->scale.x = 1;
  this->scale.y = 1;

  this->associated.angleDeg = 0;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated)
{
  this->texture = nullptr;
  this->scale.x = 1;
  this->scale.y = 1;

  this->associated.angleDeg = 0;

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
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't load Query Texture !!" << std::endl;
    std::cout << "Error Query Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
  Sprite::SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.h = h;
  this->clipRect.w = w;
}

void Sprite::Render(int x, int y, int w, int h)
{

  SDL_Renderer *render = Game::GetInstance().GetRenderer();

  const SDL_Rect dstClip = {x, y, (int) (w * this->scale.x), (int) (h * this->scale.y)};

  int render_flag = SDL_RenderCopyEx(render, this->texture, &this->clipRect, &dstClip, this->associated.angleDeg, nullptr, SDL_FLIP_NONE);

  if (render_flag != 0)
  {
    std::fstream logfile("Errors.log", fstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't Render Copy !!" << std::endl;
    std::cout << "Error Render Copy: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
}

void Sprite::Render(int x, int y)
{
  this->Render(x, y, this->width, this->height);
}

void Sprite::Render()
{
  this->Render(this->associated.box.x - Camera::pos.x, this->associated.box.y - Camera::pos.y);
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

void Sprite::SetScale(float scalex, float scaley)
{
  pair<float, float> center = this->associated.box.get_center();

  if (scalex != 0)
  {
    float center_x_before_scaling = center.first;

    this->associated.box.x = center_x_before_scaling - ((this->associated.box.w * scalex) / 2.0);

    this->scale.x = scalex;
  }

  if (scaley != 0)
  {
    float center_y_before_scaling = center.second;

    this->associated.box.y = center_y_before_scaling - ((this->associated.box.h * scaley) / 2.0);

    this->scale.y = scaley;
  }
}