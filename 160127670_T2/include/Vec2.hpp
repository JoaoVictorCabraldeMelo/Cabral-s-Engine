#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
class Vec2
{
public:
  float x, y;

  Vec2(float x, float y);

  Vec2 operator + (const Vec2 &vector);

  Vec2 operator - (const Vec2 &vector);

  Vec2 operator * (const int &scalar);

  float magnitude(Vec2 vector);

  Vec2 normalise(Vec2 vector);

  float distance(float x, float y);

  double inclination();

  double inclination_two_points(Vec2 vector);

  Vec2 rotate(double angle);

};

#endif