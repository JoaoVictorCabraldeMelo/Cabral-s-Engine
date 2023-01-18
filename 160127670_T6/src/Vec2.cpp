
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

Vec2 Vec2::operator*(float scalar)
{
  this->x *= scalar;
  this->y *= scalar;

  return *this;
}

Vec2 Vec2::operator*(Vec2 vector){
  float x = this->x * vector.x;
  float y = this->y * vector.y;

  this->x = x;
  this->y = y;

  return *this;
}

float Vec2::magnitude(Vec2 vector)
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

  float x1 = this->x / magnitude;
  float y1 = this->y / magnitude;

  this->x = x1;
  this->y = y1;

  return *this;
}

float Vec2::distance(Vec2 vector)
{
  return this->magnitude(vector);
}

double Vec2::inclination()
{
  double result = atan2(this->y, this->x); // angle in radians

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

double radians_to_degrees(float angle_in_radians)
{
  return angle_in_radians * (180 / PI);
}

double degrees_to_radians(float angle_in_degrees) {
  return angle_in_degrees * PI / 180;
}