#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

#include "State.hpp"

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
};

#endif