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

Sprite::Sprite(GameObject &associated)
: Component(associated), texture(nullptr), width(associated.box.w), height(associated.box.h),
  scale({1.0f, 1.0f}), frameCount(1), frameTime(1.0f), flip(Flip::NONE), 
  selfDestructCount(Timer()), secondsToSelfDestruct(0.0f)
{
  associated.angleDeg = 0;
}

Sprite::Sprite(GameObject &associated, const string &file, const int frameCount, const float frameTime,
               const float secondsToSelfDestruct)
: Component(associated), texture(nullptr), scale({1.0f, 1.0f}), frameCount(frameCount), frameTime(frameTime),
  flip(Flip::NONE), selfDestructCount(Timer()), secondsToSelfDestruct(secondsToSelfDestruct)
{
  Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(const std::string& file)
{

  texture = Resource::GetImage(file);

  int query = SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

  if (query != 0)
  {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't load Query Texture !!" << std::endl;
    std::cout << "Error Query Texture: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }

  int frame_width = width / frameCount;

  Sprite::SetClip(0, 0, frame_width, height);
}

void Sprite::SetClip(const int x, const int y, const int w, const int h)
{
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.h = h;
  this->clipRect.w = w;
}

void Sprite::Render(const int x, const int y, const int w, const int h) const
{

  SDL_Renderer *render = Game::GetInstance().GetRenderer();

  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  const SDL_Rect dstClip = {x, y, (int)(w * screenScale.x * scale.x), (int)(h * screenScale.y * scale.y)};

  SDL_RendererFlip flip_value = SDL_FLIP_NONE;

  if (flip == Flip::HORIZONTAL)
    flip_value = SDL_FLIP_HORIZONTAL;
  else if (flip == Flip::VERTICAL)
    flip_value = SDL_FLIP_VERTICAL;
  else if (flip == Flip::DIAGONAL)
    flip_value = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

  int render_flag = SDL_RenderCopyEx(render, texture.get(), &clipRect, &dstClip, associated.angleDeg, nullptr, flip_value);

  if (render_flag != 0)
  {
    std::fstream logfile("Errors.log", fstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't Render Copy !!" << std::endl;
    std::cout << "Error Render Copy: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
}

void Sprite::Render(const int x,const int y) const
{
  Render(x, y, width, height);
}

void Sprite::Render()
{
  Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

bool Sprite::IsOpen() const
{
  if (texture != nullptr)
    return true;
  return false;
}

void Sprite::Update(float dt)
{
  timeElapsed += dt;

  if(secondsToSelfDestruct > 0.0f) {
    selfDestructCount.Update(dt);
    if (selfDestructCount.Get() >= this->secondsToSelfDestruct) {
      associated.RequestDelete();
    }
  }

  if (timeElapsed > frameTime)
  {
    currentFrame += 1;

    int frame_width = GetWidth() / (scale.x * Game::GetInstance().GetScreenScale().x);

    if (currentFrame >= frameCount)
    {
      currentFrame = 0;
    }

    SetClip(frame_width * currentFrame, 0, frame_width, height);

    timeElapsed = 0.0F;
  }
}

bool Sprite::Is(const string& type)
{
  if (type == "Image")
    return true;
  else
    return false;
}

int Sprite::GetHeight() const
{
  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  return height * scale.y * screenScale.y;
}

int Sprite::GetWidth() const
{
  int frame_width = width / frameCount;

  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  return frame_width * scale.x * screenScale.x;
}

void Sprite::SetScale(const float scalex, const float scaley)
{
  Vec2 center = associated.box.get_center();

  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  if (scalex != 0)
  {
    float center_x_before_scaling = center.x;

    associated.box.x = ((associated.box.w * scalex * screenScale.x) / 2.0f) - center_x_before_scaling ;

    scale.x = scalex;
  }

  if (scaley != 0)
  {
    float center_y_before_scaling = center.y;

    Vec2 screenScale = Game::GetInstance().GetScreenScale();

    associated.box.y = ((associated.box.h * scaley * screenScale.y) / 2.0) - center_y_before_scaling;

    scale.y = scaley;
  }
}

void Sprite::SetFrame(const int frame)
{
  currentFrame = frame;

  Vec2 screenScale = Game::GetInstance().GetScreenScale();

  int frame_width = GetWidth() / (scale.x * screenScale.x);

  SetClip(frame_width * currentFrame, 0, frame_width, height);
}

void Sprite::SetFrameCount(const int frameCount)
{
  this->frameCount = frameCount;

  associated.box.w = GetWidth();

  currentFrame = 0;
}

void Sprite::SetFrameTime(const float frameTime)
{
  this->frameTime = frameTime;
}

void Sprite::SetFlip(const Flip value)
{
  flip = value;
}

Sprite::Flip Sprite::GetFlip() const {
  return flip;
}