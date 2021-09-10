
#include "../include/Rect.hpp"
#include <math.h>

#define PI 3.14159265

using namespace std;

Rect::Rect(float x, float y, float w, float h)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

Rect Rect::operator+(Rect box)
{
  this->x += box.x;
  this->y += box.y;

  return *this;
}

Rect Rect::operator-(Rect box)
{
  this->x -= box.x;
  this->y -= box.y;

  return *this;
}

Rect Rect::operator*(int scalar)
{
  this->x *= scalar;
  this->y *= scalar;

  return *this;
}

float Rect::magnitude(Rect box)
{
  float x1 = this->x;
  float y1 = this->y;

  float x2 = box.x;
  float y2 = box.y;

  float magnitude = sqrt(pow((x1 - x2), 2) + pow(y1 - y2, 2));

  return magnitude;
}

Rect Rect::normalize(Rect box)
{

  float magnitude = Rect::magnitude(box);

  this->x /= magnitude;
  this->y /= magnitude;

  return *this;
}

float Rect::distance(float x, float y)
{
  return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

double Rect::inclination()
{
  double result = atan2(this->x, this->y) * 180 / PI;

  return result;
}

double Rect::inclination_two_points(Rect box)
{
  Rect diference = Rect(0, 0, 0, 0);

  diference.x = box.x - this->x;
  diference.y = box.y - this->y;

  double result = atan2(diference.x, diference.y) * 180 / PI;

  return result;
}

Rect Rect::rotate(double angle)
{
  this->x = this->x * cos(angle) - this->y * sin(angle);
  this->y = this->y * cos(angle) - this->y * sin(angle);

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

  float x2 = this->x - this->h;
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
  if (x >= (this->x - h))
  {
    if (y <= (this->y + w))
      return true;
    else
      return false;
  }
  return false;
}
