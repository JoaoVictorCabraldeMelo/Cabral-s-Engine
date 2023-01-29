#ifndef _RECT_H_
#define _RECT_H_

#include <iostream>
#include "Vec2.hpp"

class Rect
{
public:
  float x, y, w, h;

  explicit Rect();

  Rect(const float x, const float y, const float w, const float h);

  Rect operator*(const Vec2& vector);

  float distance(const Vec2& vector) const;

  double inclination() const;

  double inclination_two_points(const Rect& box) const;

  Rect rotate(const double angle);

  void sum_vec(const Vec2& vector);

  Vec2 get_center() const;

  float distance_between_centers(const Rect& box) const;

  bool is_point_in(const Vec2& point) const;

  void set_center(const Vec2& point);

  void set_center_x(const float x);
};

#endif
