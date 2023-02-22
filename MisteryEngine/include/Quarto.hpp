#ifndef _QUARTO_H_
#define _QUARTO_H_

#include "State.hpp"
#include "Mixer.hpp"
#include "Timer.hpp"
#include "Focus.hpp"

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

    GameObject *dialogs;

    Mixer *music;

    Timer timer;

    GameObject *wardrobe;

    GameObject *bed;

    GameObject *door;

    static GameObject *focus;

    Focus *makeFocus;
    
  private:
    int first_time = 0;

    bool flag_initial_dialogs = false;
};

#endif 