#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include "../include/InputManager.hpp"

using namespace std;

InputManager &InputManager::GetInstance()
{
    static InputManager newInputManager;
    return newInputManager;
}

InputManager::InputManager()
{
    for (int i = 0; i < 6; i++)
    {
        this->mouseState[i] = false;
        this->mouseUpdate[i] = 0;
    }

    for (int i = 0; i < 416; i++)
    {
        this->keyState[i] = false;
        this->keyUpdate[i] = 0;
    }

    this->quitRequested = false;

    this->updateCounter = 0;

    this->mouseX = 0;
    this->mouseY = 0;
}

void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&this->mouseX, &this->mouseY);

    this->quitRequested = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            this->updateCounter++;
            this->quitRequested = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat != 1)
        {
            this->updateCounter++;
            this->mouseState[event.button.button] = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP && event.key.repeat != 1)
        {
            this->updateCounter++;
            this->mouseState[event.button.button] = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat != 1)
        {
            this->updateCounter++;
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF81;
            }

            this->keyState[newKey] = true;
        }

        if (event.type == SDL_KEYUP && event.key.repeat != 1)
        {
            this->updateCounter++;
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF81;
            }

            this->keyState[newKey] = false;
        }
    }
}