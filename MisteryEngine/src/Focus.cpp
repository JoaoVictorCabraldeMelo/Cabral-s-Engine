#include "../include/Focus.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp" 
#include "../include/Quarto.hpp"

using namespace std;


Focus::Focus() {
  current_background = nullptr;
}

Focus::~Focus() {}

void Focus::MakeFocus(float dt) {

  animation_timer.Update(dt);

  if (Quarto::focus == nullptr) {
    Quarto::focus = new GameObject();
  }

  if (animation_timer.Get() < .1F) {
    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_1.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
  else if (animation_timer.Get() >= .2F && animation_timer.Get() < .3F)
  {
    Quarto::focus->RemoveComponent(current_background);

    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_2.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
  else if (animation_timer.Get() >= .3F && animation_timer.Get() < .4F)
  {
    Quarto::focus->RemoveComponent(current_background);

    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_3.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
  else if (animation_timer.Get() >= .4F && animation_timer.Get() < .5F)
  {
    Quarto::focus->RemoveComponent(current_background);

    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_4.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
  else if (animation_timer.Get() >= .5F && animation_timer.Get() < .6F)
  {
    Quarto::focus->RemoveComponent(current_background);

    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_5.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
  else if (animation_timer.Get() >= .6F && animation_timer.Get() < .7F)
  {
    Quarto::focus->RemoveComponent(current_background);

    Sprite *background = new Sprite(*Quarto::focus, "assets/img/shadowing_6.png");

    Quarto::focus->AddComponent(background);

    current_background = background;
  }
}

void Focus::UnmakeFocus() {
  if (Quarto::focus != nullptr) {
    if (current_background != nullptr) {
      Quarto::focus->RemoveComponent(current_background);
      current_background = nullptr;
      animation_timer.Restart();
    }
  }
}