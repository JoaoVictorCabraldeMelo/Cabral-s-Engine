
#include "../include/Vec2.hpp"
#include <math.h>

extern const float PI = 3.14159265359;
extern const float DEG30 = PI / 6;
extern const float DEG45 = PI / 4;
extern const float DEG60 = PI / 3;
extern const float DEG90 = PI / 2;

Vec2::Vec2()
{
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vec2 Vec2::operator+(const Vec2 &vector)
{
  this->x += vector.x;
  this->y += vector.y;

  return *this;
}

Vec2 Vec2::operator-(const Vec2 &vector)
{
  this->x -= vector.x;
  this->y -= vector.y;

  return *this;
}

Vec2 Vec2::operator*(const int &scalar)
{
  this->x *= scalar;
  this->y *= scalar;

  return *this;
}

float Vec2::magnitude(Vec2 vector = {0, 0})
{
  float x1 = this->x;
  float y1 = this->y;

  float x2 = vector.x;
  float y2 = vector.y;

  float magnitude = sqrt(pow((x1 - x2), 2) + pow(y1 - y2, 2));

  return magnitude;
}

Vec2 Vec2::normalise()
{
  float magnitude = this->magnitude();

  this->x /= magnitude;
  this->y /= magnitude;

  return *this;
}

float Vec2::distance(float x, float y)
{
  Vec2 vector = Vec2(x, y);

  return this->magnitude(vector);
}

double Vec2::inclination()
{
  double result = atan2(this->y, this->x); // angle in radians

  // double result_in_degress = (result / PI) * 180;

  return result;
}

double Vec2::inclination_two_points(Vec2 vector)
{

  Vec2 diference = vector - *this;

  double result = diference.inclination();

  return result;
}

Vec2 Vec2::rotate(double angle)
{
  float sen = sin(angle), cosin = cos(angle);

  float x = this->x * cosin - this->y * sen;
  float y = this->x * sen + this->y * cosin;  

  this->x = x;
  this->y = y;

  return *this;
}

double Vec2::radians_to_degrees(float angle_in_radians)
{
  return angle_in_radians * (180 / PI);
}
