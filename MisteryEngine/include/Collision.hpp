#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Rect.hpp"
#include "Vec2.hpp"

class Collision {
  public:
    static bool IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB);
};

#endif