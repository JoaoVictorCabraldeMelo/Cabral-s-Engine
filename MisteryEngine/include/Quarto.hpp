#ifndef _QUARTO_H_
#define _QUARTO_H_

#include "State.hpp"
#include "Mixer.hpp"
#include "Timer.hpp"


class Quarto : public State {
  public:
    Quarto();

    ~Quarto();

    void LoadAssets() override;

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;

    GameObject *inventory;

    GameObject *inventory_icon;

    GameObject *bianca;

    GameObject *background;

    GameObject *mouse;

    GameObject *loading_screen;

    GameObject *dialog_screen;

    Mixer *music;

    Timer timer;
  private:
    int first_time = 0;
};

#endif 