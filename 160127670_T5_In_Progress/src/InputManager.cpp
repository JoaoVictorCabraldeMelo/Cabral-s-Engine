#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include "../include/InputManager.hpp"

#include <iostream>

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

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&this->mouseX, &this->mouseY);

    this->quitRequested = false;

    this->updateCounter++;

     while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            this->quitRequested = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat != 1)
        {
            int newButton = (int) event.button.button;

            this->mouseState[newButton] = true;
            this->mouseUpdate[newButton] = this->updateCounter;
        }

        if (event.type == SDL_MOUSEBUTTONUP && event.key.repeat != 1)
        {
            int newButton = (int)event.button.button;

            this->mouseState[newButton] = false;
            this->mouseUpdate[newButton] = this->updateCounter;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat != 1)
        {
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF80;
            }

            this->keyState[newKey] = true;
            this->keyUpdate[newKey] = this->updateCounter;
        }

        if (event.type == SDL_KEYUP && event.key.repeat != 1)
        {
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF80;
            }

            this->keyState[newKey] = false;
            this->keyUpdate[newKey] = this->updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    if (this->keyUpdate[newKey] == this->updateCounter)
        return this->keyState[newKey];

    return false;
}

bool InputManager::KeyRelease(int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    if (this->keyUpdate[newKey] == this->updateCounter)
        return !this->keyState[newKey];

    return false;
}

bool InputManager::MousePress(int button)
{
    if (this->mouseUpdate[button] == this->updateCounter)
        return this->mouseState[button];

    return false;
}

bool InputManager::MouseRelease(int button)
{
    if (this->mouseUpdate[button] == this->updateCounter)
        return !this->mouseState[button];

    return false;
}

bool InputManager::isKeyDown(int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    return this->keyState[newKey];
}

bool InputManager::isMouseDown(int button)
{
    return this->mouseState[button];
}

int InputManager::GetMouseX()
{
    return this->mouseX;
}

int InputManager::GetMouseY()
{
    return this->mouseY;
}

bool InputManager::QuitRequested()
{
    return this->quitRequested;
}