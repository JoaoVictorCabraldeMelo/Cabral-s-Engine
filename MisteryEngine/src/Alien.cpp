#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Vec2.hpp"
#include "../include/Minion.hpp"
#include "../include/Game.hpp"
#include "../include/Collider.hpp"
#include "../include/Bullet.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/PenguinCannon.hpp"

#include <iostream>
#include <fstream>

using namespace std;

size_t Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(50.0F, 50.0F)
{

  Sprite *alien_sprite = new Sprite(associated, "assets/img/alien.png");

  Collider *collider_alien = new Collider(associated);

  this->associated.AddComponent(alien_sprite);
  this->associated.AddComponent(collider_alien);

  this->nMinions = nMinions;

  this->hp = 50;

  this->associated.box.w = alien_sprite->GetWidth();
  this->associated.box.h = alien_sprite->GetHeight();

  this->state = RESTING;
  this->restTimer = Timer();

  ++alienCount;
}

Alien::~Alien()
{
  this->minionArray.clear();
  --alienCount;
}

void Alien::Start()
{
  Game &instance = Game::GetInstance();

  State &game_state = instance.GetState();

  weak_ptr<GameObject> alien_go = game_state.GetObjectPtr(&this->associated);

  for (int i = 0; i < this->nMinions; i++)
  {
    GameObject *minion_go = new GameObject();

    Component *minion = new Minion(*minion_go, alien_go, i * ((2 * PI) / this->nMinions));

    minion_go->AddComponent(minion);

    weak_ptr<GameObject> weak_go = game_state.AddObject(minion_go);

    this->minionArray.push_back(weak_go);
  }
}

void Alien::Update(float dt)
{
  float x = 0;
  float y = 0;

  if(this->restTimer.Get() <= 3.0F && this->state == RESTING){
    this->restTimer.Update(dt);
    this->state = RESTING;
  }
  else {
    this->restTimer.Restart();
    x = PenguinBody::player->associated.box.x;
    y = PenguinBody::player->associated.box.y;

    this->destination = Vec2(x, y);

    this->state = MOVING;
  }

  // cout << "X: " <<  this->destination.x << " Y: " << this->destination.y << endl;

  float angle_clockwise_degrees = -(DEG30 * 180 / PI) * dt;

  this->associated.angleDeg += angle_clockwise_degrees;

  if (this->state == MOVING) {

    Vec2 alien_center = this->associated.box.get_center();

    float distance = this->destination.distance(alien_center);

    Vec2 result_position = Vec2::Sub(this->destination, alien_center);

    result_position = Vec2::Norm(result_position);

    if (distance <= 500.0F)
    {
      float min_distance = MAXFLOAT;

      int minion_index = 0;

      for (int i = 0; i < this->nMinions; i++)
      {
        Rect minion_box = this->minionArray[i].lock()->box;

        float current_distance = minion_box.distance(this->destination);

        if (current_distance < min_distance)
        {
          min_distance = current_distance;
          minion_index = i;
        }
      }

      GameObject *minion_ptr = this->minionArray[minion_index].lock().get();

      Minion *minion_cpt = static_cast<Minion *>(minion_ptr->GetComponent("Minion"));

      minion_cpt->Shoot(this->destination);

      this->state = RESTING;
    }
    else
    {
      Vec2 new_position = result_position * this->speed * dt;

      this->associated.box.x += new_position.x;
      this->associated.box.y += new_position.y;

      this->state = MOVING;
    }
  }

  if (this->hp <= 0)
    this->associated.RequestDelete();
  
}

void Alien::Render()
{
}

bool Alien::Is(string type)
{
  if (type == "Alien")
    return true;
  return false;
}

void Alien::NotifyCollision(GameObject &other) {

  Bullet *maybe_bullet = static_cast<Bullet *> (other.GetComponent("Bullet"));

  if (maybe_bullet) {
    if(!maybe_bullet->targetsPlayer){
      this->hp -= maybe_bullet->GetDamage();
      if (this->hp <= 0)
      {
        GameObject *death_explosion = new GameObject();

        Sprite *sprite_death = new Sprite(*death_explosion, "assets/img/aliendeath.png", 4, .25F, 1.0F);
        sprite_death->SetScale(.25F, .5F);
        Music *explosion_sound = new Music(*death_explosion, "assets/audio/boom.wav");
        explosion_sound->Play();

        death_explosion->AddComponent(sprite_death);
        death_explosion->AddComponent(explosion_sound);

        death_explosion->box.x = this->associated.box.x;
        death_explosion->box.y = this->associated.box.y;

        State &game_state = Game::GetInstance().GetState();

        game_state.AddObject(death_explosion);
      }
    }
  }
}
