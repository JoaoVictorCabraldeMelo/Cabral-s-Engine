#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

#include "State.hpp"
#include "Timer.hpp"
#include "Text.hpp"

class TitleState : public State {
  public:
    TitleState();

    ~TitleState();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Start();

    void Pause();

    void Resume();
  
  private:
    Timer blink;
    
    Text *title_text;
};

#endif