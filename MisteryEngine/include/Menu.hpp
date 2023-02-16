#ifndef _MENU_H_
#define _MENU_H_

#include "State.hpp"
#include "Mixer.hpp"

class Menu : public State {
  public:
      Menu();

      ~Menu();

      Menu(Menu& menu) = delete;

      void LoadAssets() override;

      void Update(float dt) override;

      void Render() override;

      void Start() override;

      void Pause() override;

      void Resume() override;

  private:
    enum class MenuButton
    {
      START,
      CONFIG,
      QUIT
    };

    MenuButton button = MenuButton::START;

    Mixer *music;

    Mixer *switch_button;

    Mixer *click;
};

#endif