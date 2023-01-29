#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
class Vec2
{
public:
  float x, y;

  static constexpr float PI = 3.14159265359;
  
  static constexpr float DEG30 = PI / 6;

  static constexpr float DEG45 = PI / 4;

  static constexpr float DEG60 = PI / 3;

  static constexpr float DEG90 = PI / 2;

  explicit Vec2();

  Vec2(float x, float y);

  Vec2 operator + (const Vec2 &vector);

  Vec2 operator - (const Vec2 &vector);

  Vec2 operator * (float scalar);

  Vec2 operator*(Vec2 vector);

  float magnitude(Vec2 vector = {0.0F, 0.0F}) const;

  Vec2 normalise();

  float distance(Vec2 vector) const;

  double inclination() const;

  double inclination_two_points(Vec2 vector) const;

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