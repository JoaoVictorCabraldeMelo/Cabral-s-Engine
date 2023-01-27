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

  this->frameCount = 1;
  this->frameTime = 1.0F;

  this->secondsToSelfDestruct = 0.0F;

  this->selfDestructCount = Timer();

  this->associated.angleDeg = 0;

  this->flip = Flip::NONE;
}

Sprite::Sprite(GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated)
{
  this->texture = nullptr;
  this->scale.x = 1;
  this->scale.y = 1;

  this->associated.angleDeg = 0;

  this->frameCount = frameCount;
  this->frameTime = frameTime;

  this->secondsToSelfDestruct = secondsToSelfDestruct;
  this->selfDestructCount = Timer();

  this->flip = Flip::NONE;

  this->Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string file)
{

  this->texture = Resource::GetImage(file);

  int query = SDL_QueryTexture(this->texture.get(), nullptr, nullptr, &this->width, &this->height);

  if (query != 0)
  {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't load Query Texture !!" << std::endl;
    std::cout << "Error Query Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  int frame_width = this->width / this->frameCount;

  Sprite::SetClip(0, 0, frame_width, this->height);
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

  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  const SDL_Rect dstClip = {x, y, (int)(w * screenScale.x * this->scale.x), (int)(h * screenScale.y * this->scale.y)};

  SDL_RendererFlip flip_value = SDL_FLIP_NONE;

  if (this->flip == Flip::HORIZONTAL)
    flip_value = SDL_FLIP_HORIZONTAL;
  else if (this->flip == Flip::VERTICAL)
    flip_value = SDL_FLIP_VERTICAL;
  else if (this->flip == Flip::DIAGONAL)
    flip_value = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

  int render_flag = SDL_RenderCopyEx(render, this->texture.get(), &this->clipRect, &dstClip, this->associated.angleDeg, nullptr, flip_value);


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
  this->timeElapsed += dt;

  if(this->secondsToSelfDestruct > 0.0f) {
    this->selfDestructCount.Update(dt);
    if (this->selfDestructCount.Get() >= this->secondsToSelfDestruct) {
      this->associated.RequestDelete();
    }
  }

  if (this->timeElapsed > this->frameTime)
  {
    this->currentFrame += 1;

    int frame_width = this->GetWidth() / this->scale.x;

    if (this->currentFrame >= this->frameCount)
    {
      this->currentFrame = 0;
    }

    this->SetClip(frame_width * this->currentFrame, 0, frame_width, this->height);

    this->timeElapsed = 0.0F;
  }
}

bool Sprite::Is(const string type)
{
  if (type == "Image")
    return true;
  else
    return false;
}

int Sprite::GetHeight()
{
  return this->height * this->scale.y;
}

int Sprite::GetWidth()
{
  int frame_width = this->width / this->frameCount;

  return frame_width * this->scale.x;
}

void Sprite::SetScale(float scalex, float scaley)
{
  Vec2 center = this->associated.box.get_center();

  if (scalex != 0)
  {
    float center_x_before_scaling = center.x;

    this->associated.box.x = center_x_before_scaling - ((this->associated.box.w * scalex) / 2.0);

    this->scale.x = scalex;
  }

  if (scaley != 0)
  {
    float center_y_before_scaling = center.y;

    this->associated.box.y = center_y_before_scaling - ((this->associated.box.h * scaley) / 2.0);

    this->scale.y = scaley;
  }
}

void Sprite::SetFrame(int frame)
{
  this->currentFrame = frame;

  int frame_width = this->GetWidth() / this->scale.x;

  this->SetClip(frame_width * currentFrame, 0, frame_width, this->height);
}

void Sprite::SetFrameCount(int frameCount)
{
  this->frameCount = frameCount;

  this->associated.box.w = this->GetWidth();

  this->currentFrame = 0;
}

void Sprite::SetFrameTime(float frameTime)
{
  this->frameTime = frameTime;
}

void Sprite::SetFlip(Flip value)
{
  this->flip = value;
}

Sprite::Flip Sprite::GetFlip(){
  return this->flip;
}