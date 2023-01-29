
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include "../include/CameraFollower.hpp"
#include "../include/GameObject.hpp"
#include "../include/Camera.hpp"

using namespace std;

CameraFollower::CameraFollower(GameObject &associated) : Component(associated)
{
}

void CameraFollower::Update(float dt)
{
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {}

bool CameraFollower::Is(const string& type)
{
    return "CameraFollower" == type;
}
