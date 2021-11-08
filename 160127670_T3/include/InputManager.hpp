#ifndef INPUT_MANAGER
#define INPUT_MANAGER

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