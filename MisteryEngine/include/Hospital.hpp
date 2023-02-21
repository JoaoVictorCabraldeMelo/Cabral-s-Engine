#ifndef _Hospital_H_
#define _Hospital_H_

#include "State.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Mixer.hpp"

class Hospital : public State {
  public:
    Hospital();

    ~Hospital();

    void LoadAssets() override;

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;

    GameObject *inventory;

    GameObject *inventory_icon;

    GameObject *bianca;

    GameObject *soro;

    GameObject *background;

    GameObject *mouse;

    GameObject *loading_screen;

  private:

    Timer timer;

    Mixer *music;

    int first_time = 0;
};

#endif