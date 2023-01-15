#ifndef _BULLET_H_
#define _BULLET_H_

#include "Component.hpp"
#include "Vec2.hpp"

const float BULLET_SPEED = 200.0;
class Bullet : public Component
{
  public:
    Bullet(GameObject &associated, float angle, float speed, int frames, int damage, float max_distance, std::string sprite);

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    int GetDamage();

  private:
    Vec2 speed;

    float distance_left;
    
    int damage;
};

#endif