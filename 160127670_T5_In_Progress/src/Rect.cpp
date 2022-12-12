
#include "../include/Rect.hpp"
#include <math.h>

#define PI 3.14159265

using namespace std;

Rect::Rect()
{
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}

Rect::Rect(float x, float y, float w, float h)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

float Rect::distance(float x, float y)
{
  return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

//Vec a e Vec b sao utilizados na rotacao de matriz 
Rect Rect::rotate(double angle)
{

  Vec2 a = {cos(angle), sin(angle)};
  Vec2 b = {-sin(angle), cos(angle)};


  this->x = this->x * a.x + this->x * a.y;

  this->y = this->y * b.x + this->y * b.y;

  return *this;
}

void Rect::sum_vec(Vec2 vector)
{
  this->x += vector.x;
  this->y += vector.y;
}

pair<float, float> Rect::get_center()
{
  pair<float, float> center;

  float x2 = this->x + this->h;
  float y2 = this->y + this->w;

  center.first = (this->x + x2) / 2;
  center.second = (this->y + y2) / 2;

  return center;
}

pair<float, float> Rect::distance_between_centers(Rect box)
{
  pair<float, float> result;

  result.first = this->get_center().first - box.get_center().first;
  result.second = this->get_center().second - box.get_center().second;

  return result;
}

bool Rect::is_point_in(float x, float y)
{

  if (x <= (this->x + w) && x >= this->x)
  {
    if (y <= (this->y + h) && y >= this->y)
      return true;
    else
      return false;
  }
  return false;
}
