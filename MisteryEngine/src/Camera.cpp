#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include "../include/Camera.hpp"
#include "../include/GameObject.hpp"
#include "../include/InputManager.hpp"
#include "../include/Game.hpp"

GameObject *Camera::focus = nullptr;

Vec2 Camera::pos = Vec2(0, 0);

Vec2 Camera::speed = Vec2(300, 300);

void Camera::Follow(GameObject *newFocus)
{
  focus = newFocus;
}

void Camera::Unfollow()
{
  focus = nullptr;
}

void Camera::Update(float dt)
{
  if (focus == nullptr)
  {
    pos.x = 0;
    pos.y = 0;
  }
  else
  {
    Game &game = Game::GetInstance();

    pos.x = focus->box.x - (float) (game.GetWidth() / 2.0);
    pos.y = focus->box.y - (float) (game.GetHeight() / 2.0);
  }
}