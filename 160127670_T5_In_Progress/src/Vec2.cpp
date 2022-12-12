
#include "../include/Vec2.hpp"
#include <math.h>

extern const float PI = 3.14159265;

Vec2::Vec2() {
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
  double result = atan2(this->x, this->y) * 180 / PI;

  return result;
}

double Vec2::inclination_two_points(Vec2 vector)
{
  Vec2 diference = Vec2(0, 0);

  diference.x = vector.x - this->x;
  diference.y = vector.y - this->y;

  double result = diference.inclination();

  return result;
}

Vec2 Vec2::rotate(double angle)
{
  this->x = this->x * cos(angle) - this->y * sin(angle);
  this->y = this->y * cos(angle) - this->y * sin(angle);

  return *this;
}
