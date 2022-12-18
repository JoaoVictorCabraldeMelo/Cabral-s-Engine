#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Vec2.hpp"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

extern const float PI;

const float degree60 = PI / 3;

const float degree45 = PI / 4;

const float degree90 = PI / 2;

const float degree30 = PI / 6;

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated), alienCenter(alienCenter)
{

    Component *minion_sprite = new Sprite(associated, "assets/img/minion.png");

    this->associated.AddComponent(minion_sprite);

    this->arc = arcOffsetDeg;
}

void Minion::Update(float dt)
{
    Vec2 distance_minion_origen {0, 0};

    if (this->arc == 0)
    {
        distance_minion_origen.x = 200;
        distance_minion_origen.y = 0;
    }

    float speed = degree30 * dt;

    this->arc += speed;

    distance_minion_origen.rotate(arc);

    shared_ptr<GameObject> new_alien_center = this->alienCenter.lock();

    if (new_alien_center.get() != nullptr)
    {
        GameObject &updt_alien_center = *new_alien_center.get();

        distance_minion_origen.x += updt_alien_center.box.x;
        distance_minion_origen.y += updt_alien_center.box.y;

        this->associated.box.x = distance_minion_origen.x;
        this->associated.box.y = distance_minion_origen.y;
    }
    else
    {
        this->associated.RequestDelete();
        return;
    }
}

void Minion::Render()
{
}

bool Minion::Is(string type)
{
    if (type == "Minion")
        return true;
    return false;
}

void Minion::Shoot(Vec2 target)
{
}