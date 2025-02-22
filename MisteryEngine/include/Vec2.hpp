#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
class Vec2
{
public:
  float x, y;

  Vec2();

  Vec2(float x, float y);

  Vec2 operator + (const Vec2 &vector);

  Vec2 operator - (const Vec2 &vector);

  Vec2 operator * (float scalar);

  Vec2 operator*(Vec2 vector);

  float magnitude(Vec2 vector = {0.0F, 0.0F});

  Vec2 normalise();

  float distance(Vec2 vector);

  double inclination();

  double inclination_two_points(Vec2 vector);

  Vec2 rotate(double angle);

  static Vec2 Sub(const Vec2 &vectorA, const Vec2 &vectorB);

  static Vec2 Sum(const Vec2 &vectorA, const Vec2 &vectorB);

  static Vec2 Rot(const Vec2 &vector, float angleRad);

  static Vec2 Norm(const Vec2 &vector);

  static double Mag(const Vec2 &vector);

  static double Dot(const Vec2 &vectorA, const Vec2 &vectorB);
};


double radians_to_degrees(float angle_in_radians);

double degrees_to_radians(float angle_in_degrees);

#endif