#ifndef _RECT_H_
#define _RECT_H_

#include <iostream>
#include "Vec2.hpp"

class Rect
{
public:
  float x, y, w, h;

  Rect();

  Rect(float x, float y, float w, float h);

  Rect operator*(Vec2 vector);

  float distance(Vec2 vector);

  double inclination();

  double inclination_two_points(Rect box);

  Rect rotate(double angle);

  void sum_vec(Vec2 vector);

  Vec2 get_center();

  float distance_between_centers(Rect box);

  bool is_point_in(Vec2 point);

  void set_center(Vec2 point);
};

#endif
