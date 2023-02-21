#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d
#define P_KEY SDLK_CAPSLOCK
#define SPACE_KEY SDLK_SPACE
#define ENTER_KEY SDLK_RETURN
#define TAB_KEY SDLK_TAB

#include <memory>


class InputManager
{
private:
    bool mouseState[6];
    int mouseUpdate[6];

    bool keyState[416];
    int keyUpdate[416];

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;


public:
    InputManager(/* args */);
    ~InputManager();

    void Update();

    bool KeyPress(const int key);
    bool KeyRelease(const int key);
    bool isKeyDown(const int key);

    bool MousePress(const int button);
    bool MouseRelease(const int button);
    bool isMouseDown(const int button);

    int GetMouseX() const ;
    int GetMouseY() const;

    bool QuitRequested() const ;

    static InputManager &GetInstance();

};



#endif