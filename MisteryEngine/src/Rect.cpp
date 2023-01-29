
#include "../include/Rect.hpp"
#include <math.h>

#define PI 3.14159265

using namespace std;

Rect::Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f)
{}

Rect::Rect(const float x, const float y, const float w, const float h)
: x(x), y(y), w(w), h(h)
{}

Rect Rect::operator*(const Vec2& vector){
  float new_w = w * vector.x;
  float new_h = h * vector.y;

  Rect new_rect{x, y, new_w, new_h};

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

  x = x * cos(angle) - y * sin(angle);

  y = x * sin(angle) + y * cos(angle);

  return *this;
}

void Rect::sum_vec(const Vec2& vector)
{
  x += vector.x;
  y += vector.y;
}

Vec2 Rect::get_center() const
{
  Vec2 center;

  center.x = x  + (float) (w / 2.0);
  center.y = y + (float) (h / 2.0);

  return center;
}

void Rect::set_center(const Vec2& point){

  float new_x = point.x - (float)(w / 2.0);
  float new_y = point.y - (float)(h / 2.0);

  x = new_x;
  y = new_y;
}

void Rect::set_center_x(const float x) {
  float new_x = x - (float)(w / 2.0f);
  this->x = new_x;
}

float Rect::distance_between_centers(const Rect& box) const
{
  Vec2 destiny { box.get_center().x, box.get_center().y};
  Vec2 initial{ get_center().x,  get_center().y};

  float distance = initial.distance(destiny);

  return distance;
}

bool Rect::is_point_in(const Vec2& point) const
{

  if (x + w >= point.x && x <= point.x)
  {
    if (y + h >= point.y && y <= point.y)
      return true;
    else
      return false;
  }
  return false;
}
