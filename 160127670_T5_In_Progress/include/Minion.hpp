#ifndef _MINION_H_
#define _MINION_H_

#include "Component.hpp"
#include "Vec2.hpp"

class Minion : public Component
{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};

#endif