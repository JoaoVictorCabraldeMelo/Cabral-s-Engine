#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Vec2.hpp"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated), alienCenter(*alienCenter.lock().get())
{

    Sprite *minion_sprite = new Sprite(associated, "assets/img/minion.png");

    this->associated.AddComponent(minion_sprite);

    this->arc = arcOffsetDeg;

    this->associated.box.w = minion_sprite->GetWidth();

    this->associated.box.h = minion_sprite->GetHeight();
}

void Minion::Start()
{
}

void Minion::Update(float dt)
{
    Vec2 distance_minion_origen{0, 0};

    float ratio = 200;

    if (this->arc == 0)
    {
        distance_minion_origen.x = ratio;
        distance_minion_origen.y = 0;
    }

    float speed = DEG30 * dt;

    this->arc += speed;

    // simple rotation
    distance_minion_origen.x = ratio * cos(this->arc);
    distance_minion_origen.y = ratio * sin(this->arc);

    if (&this->alienCenter != nullptr)
    {
        GameObject &updt_alien_center = this->alienCenter;

        pair<float, float> center = updt_alien_center.box.get_center();

        distance_minion_origen.x += center.first - 10;
        distance_minion_origen.y += center.second + 5;

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