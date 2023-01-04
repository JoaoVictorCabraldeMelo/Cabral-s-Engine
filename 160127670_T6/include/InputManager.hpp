#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define W_KEY SDL_SCANCODE_W
#define S_KEY SDL_SCANCODE_S
#define A_KEY SDL_SCANCODE_A
#define D_KEY SDL_SCANCODE_D


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

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool isKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool isMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager &GetInstance();

};



#endif