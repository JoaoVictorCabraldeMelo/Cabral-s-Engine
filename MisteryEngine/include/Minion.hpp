#ifndef _MINION_H_
#define _MINION_H_

#include "Component.hpp"
#include "Vec2.hpp"

extern const float PI;

extern const float DEG30;
extern const float DEG45;
extern const float DEG60;
extern const float DEG90;

    

class Minion : public Component
{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
    void Start();
    void NotifyCollision(GameObject &other);

private:
    GameObject& alienCenter;
    float arc;
};

#endif