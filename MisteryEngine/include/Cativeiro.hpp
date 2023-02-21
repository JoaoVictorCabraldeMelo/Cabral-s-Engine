#ifndef _Cativeirop_H_
#define _Cativeirop_H_

#include "State.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Mixer.hpp"

class Cativeiro : public State {
  public:
    Cativeiro();

    ~Cativeiro();

    void LoadAssets() override;

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;

    GameObject *inventory;

    GameObject *inventory_icon;

    GameObject *bianca;

    GameObject *tv;

    GameObject *phone;

    GameObject *background;

    GameObject *mouse;

    GameObject *loading_screen;

  private:

    Timer timer;

    Mixer *music;

    int first_time = 0;
};

#endif