#ifndef _FOCUS_H_
#define _FOCUS_H_

#include "Timer.hpp"
#include "Component.hpp"

class Focus {
  public:
    Focus();

    ~Focus();

    void MakeFocus(float dt);

    void UnmakeFocus();

  private:
    Timer animation_timer = Timer();

    Component *current_background;
};

#endif