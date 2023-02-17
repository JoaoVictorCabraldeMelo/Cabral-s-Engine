#ifndef _CHAPTER_ONE_H_
#define _CHAPTER_ONE_H_

#include "State.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Mixer.hpp"

class ChapterOne : public State {
  public:
    ChapterOne();

    ~ChapterOne();

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