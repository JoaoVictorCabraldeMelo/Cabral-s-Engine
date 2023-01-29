
#include "../include/Vec2.hpp"
#include <math.h>

Vec2::Vec2() 
: x(0.0f), y(0.0f)
{
}

Vec2::Vec2(float x, float y)
: x(x), y(y)
{
}

Vec2 Vec2::operator+(const Vec2 &vector)
{
  x += vector.x;
  y += vector.y;

  return *this;
}

Vec2 Vec2::operator-(const Vec2 &vector)
{
  x -= vector.x;
  y -= vector.y;

  return *this;
}

Vec2 Vec2::operator*(float scalar)
{
  x *= scalar;
  y *= scalar;

  return *this;
}

Vec2 Vec2::operator*(Vec2 vector){
  float x = this->x * vector.x;
  float y = this->y * vector.y;

  this->x = x;
  this->y = y;

  return *this;
}

float Vec2::magnitude(Vec2 vector) const
{
  float x1 = x;
  float y1 = y;

  float x2 = vector.x;
  float y2 = vector.y;

  float magnitude = sqrt(pow((x2 - x1), 2) + pow(y2 - y1, 2));

  return magnitude;
}

Vec2 Vec2::normalise()
{
  float magnitude = this->magnitude();

  float x1 = x / magnitude;
  float y1 = y / magnitude;

  x = x1;
  y = y1;

  return *this;
}

float Vec2::distance(Vec2 vector) const
{
  return this->magnitude(vector);
}

/* return angle in radians */
double Vec2::inclination() const
{
  double result = atan2(y, x); 

  return result;
}

double Vec2::inclination_two_points(Vec2 vector) const
{

  Vec2 initial_point{x, y};

  Vec2 diference = Vec2::Sub(vector, initial_point);
  
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

Vec2 Vec2::Sub(const Vec2& vectorA, const Vec2& vectorB){
  float x = vectorA.x - vectorB.x;
  float y = vectorA.y - vectorB.y;

  return Vec2(x, y);
}

Vec2 Vec2::Sum(const Vec2& vectorA, const Vec2& vectorB){
  float x = vectorA.x + vectorB.x;
  float y = vectorA.y + vectorB.y;

  return Vec2(x, y);
}

Vec2 Vec2::Rot(const Vec2& vector, float angleRad){
  float sen = sin(angleRad), cosin = cos(angleRad);

  float x = vector.x * cosin + vector.y * sen;
  float y = vector.x * sen - vector.y * cosin;

  return Vec2(x, y);
}

double Vec2::Mag(const Vec2 &vector) {
  return hypot(vector.x, vector.y);
}

Vec2 Vec2::Norm(const Vec2 &vector) {
  float x = vector.x * (1.0F / Vec2::Mag(vector));
  float y = vector.y * (1.0F / Vec2::Mag(vector));

  return Vec2(x, y);
}

double Vec2::Dot(const Vec2 &vectorA, const Vec2 &vectorB)
{
  return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

double radians_to_degrees(float angle_in_radians)
{
  return angle_in_radians * (180 / Vec2::PI);
}

double degrees_to_radians(float angle_in_degrees) {
  return angle_in_degrees * Vec2::PI / 180;
}

