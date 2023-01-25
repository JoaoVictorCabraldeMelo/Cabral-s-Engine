#ifndef _END_STATE_H_
#define _END_STATE_H_

#include "State.hpp"
#include "Music.hpp"

class EndState : public State {
  public:
    EndState();

    ~EndState();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Start();

    void Pause();

    void Resume();
  
  private:
    Music *backgroundMusic;
};

#endif 