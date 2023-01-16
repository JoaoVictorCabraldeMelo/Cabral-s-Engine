#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Vec2.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated), alienCenter(*alienCenter.lock().get())
{

    Sprite *minion_sprite = new Sprite(associated, "assets/img/minion.png");

    float scale = 1.0F + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.5F-1.0F)));

    minion_sprite->SetScale(scale, scale);

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
    Vec2 distance_minion_origen{125, 0};

    float ratio = 125;

    if (this->arc == 0)
    {
        distance_minion_origen.x = ratio;
        distance_minion_origen.y = 0;
    }

    float speed = DEG45 * dt;

    this->associated.angleDeg += - radians_to_degrees(speed);

    this->arc += speed;

    distance_minion_origen.rotate(this->arc);

    if (&this->alienCenter != nullptr)
    {
        GameObject &updt_alien_center = this->alienCenter;

        pair<float, float> center = updt_alien_center.box.get_center();

        distance_minion_origen.x += center.first;
        distance_minion_origen.y += center.second;

        this->associated.box.set_center(distance_minion_origen.x, distance_minion_origen.y);
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
    Game &instance = Game::GetInstance();

    State &game_state = instance.GetState();

    pair<float, float> center = this->associated.box.get_center();

    Vec2 minion_pos{center.first, center.second};

    float distance = minion_pos.distance(target.x, target.y);

    float angle_bullet = minion_pos.inclination_two_points(target);

    float angle_degress_bullet = radians_to_degrees(angle_bullet);

    GameObject *bullet_go = new GameObject();

    bullet_go->box.x = minion_pos.x;

    bullet_go->box.y = minion_pos.y;

    string sprite = "assets/img/minionbullet2.png";

    Component *bullet = new Bullet(*bullet_go, angle_degress_bullet, 100, 3, 10, distance, sprite);

    bullet_go->AddComponent(bullet);

    game_state.AddObject(bullet_go);
}