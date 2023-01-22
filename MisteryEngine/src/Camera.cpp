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
        if (InputManager::GetInstance().isKeyDown(SDLK_UP))
        {
            pos.y -= speed.y * dt;
        }

        if (InputManager::GetInstance().isKeyDown(SDLK_DOWN))
        {
            pos.y += speed.y * dt;
        }

        if (InputManager::GetInstance().isKeyDown(SDLK_LEFT))
        {
            pos.x -= speed.x * dt;
        }

        if (InputManager::GetInstance().isKeyDown(SDLK_RIGHT))
        {
            pos.x += speed.x * dt;
        }
    }else {
        Game &game = Game::GetInstance();
    
        pos.x = focus->box.x - (float) (game.GetWidth() / 2.0);
        pos.y = focus->box.y - (float) (game.GetHeight() / 2.0);
    }
}