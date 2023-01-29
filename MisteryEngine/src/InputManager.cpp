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
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    for (int i = 0; i < 416; i++)
    {
        keyState[i] = false;
        keyUpdate[i] = 0;
    }

    quitRequested = false;

    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;

    updateCounter++;

     while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat != 1)
        {
            int newButton = (int) event.button.button;

            mouseState[newButton] = true;
            mouseUpdate[newButton] = updateCounter;
        }

        if (event.type == SDL_MOUSEBUTTONUP && event.key.repeat != 1)
        {
            int newButton = (int)event.button.button;

            mouseState[newButton] = false;
            mouseUpdate[newButton] = updateCounter;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat != 1)
        {
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF80;
            }

            keyState[newKey] = true;
            keyUpdate[newKey] = updateCounter;
        }

        if (event.type == SDL_KEYUP && event.key.repeat != 1)
        {
            int newKey = event.key.keysym.sym;
            if (event.key.keysym.sym >= 0x40000000)
            {
                newKey -= 0x3FFFFF80;
            }

            keyState[newKey] = false;
            keyUpdate[newKey] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(const int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    if (keyUpdate[newKey] == updateCounter)
        return keyState[newKey];

    return false;
}

bool InputManager::KeyRelease(const int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    if (keyUpdate[newKey] == updateCounter)
        return !keyState[newKey];

    return false;
}

bool InputManager::MousePress(const int button)
{
    if (mouseUpdate[button] == updateCounter)
        return mouseState[button];

    return false;
}

bool InputManager::MouseRelease(const int button)
{
    if (mouseUpdate[button] == updateCounter)
        return !mouseState[button];

    return false;
}

bool InputManager::isKeyDown(const int key)
{
    int newKey = key;
    if (key >= 0x40000000)
        newKey -= 0x3FFFFF80;

    return keyState[newKey];
}

bool InputManager::isMouseDown(const int button)
{
    return mouseState[button];
}

int InputManager::GetMouseX() const
{
    return mouseX;
}

int InputManager::GetMouseY() const 
{
    return mouseY;
}

bool InputManager::QuitRequested() const
{
    return quitRequested;
}