
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

Rect Rect::operator*(const Vec2& vector){
  float new_w = this->w * vector.x;
  float new_h = this->h * vector.y;

  Rect new_rect{this->x, this->y, new_w, new_h};

  return new_rect;
}

float Rect::distance(const Vec2& vector) const
{
  Vec2 center{x, y};

  return center.distance(vector);
}

//Vec a e Vec b sao utilizados na rotacao de matriz 
Rect Rect::rotate(const double angle)
{

  this->x = this->x * cos(angle) - this->y * sin(angle);

  this->y = this->x * sin(angle) + this->y * cos(angle);

  return *this;
}

void Rect::sum_vec(const Vec2& vector)
{
  this->x += vector.x;
  this->y += vector.y;
}

Vec2 Rect::get_center() const
{
  Vec2 center;

  center.x = this->x  + (float) (this->w / 2.0);
  center.y = this->y + (float) (this->h / 2.0);

  return center;
}

void Rect::set_center(const Vec2& point){

  float new_x = point.x - (float)(this->w / 2.0);
  float new_y = point.y - (float)(this->h / 2.0);

  this->x = new_x;
  this->y = new_y;
}

void Rect::set_center_x(const float x) {
  float new_x = x - (float)(this->w / 2.0f);
  this->x = new_x;
}

float Rect::distance_between_centers(const Rect& box) const
{
  Vec2 destiny { box.get_center().x, box.get_center().y};
  Vec2 initial{this->get_center().x, this->get_center().y};

  float distance = initial.distance(destiny);

  return distance;
}

bool Rect::is_point_in(const Vec2& point) const
{

  if (this->x + this->w >= point.x && this->x <= point.x)
  {
    if (this->y + this->h >= point.y && this->y <= point.y)
      return true;
    else
      return false;
  }
  return false;
}
