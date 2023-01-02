
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

  this->x = this->x * cos(angle) - this->y * sin(angle);

  this->y = this->x * sin(angle) + this->y * cos(angle);

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


  center.first = this->x  + this->w / 3;
  center.second = this->y + this->h / 3;

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
