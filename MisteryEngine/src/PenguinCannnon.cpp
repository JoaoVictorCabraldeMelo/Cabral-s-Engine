#include "../include/PenguinCannon.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Bullet.hpp"
#include "../include/Collider.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/Mixer.hpp"

using namespace std;

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody)
  : Component(associated)
{
  Sprite *penguin_cannon_sprite = new Sprite(associated, "assets/img/cubngun.png");
  Collider *penguin_cannon_collider = new Collider(associated);

  associated.AddComponent(penguin_cannon_sprite);
  associated.AddComponent(penguin_cannon_collider);

  this->pbody = penguinBody;

  this->angle = 0.0F;

  this->cooldown = Timer();

  associated.box.w = penguin_cannon_sprite->GetWidth();
  associated.box.h = penguin_cannon_sprite->GetHeight();
};

void PenguinCannon::Update(float dt) {
  GameObject *go = this->pbody.lock().get();

  if (go == NULL)
  {
    this->associated.RequestDelete();
  }

  if (!this->cooldown.initialize)
    this->cooldown.Update(dt);
  

  Vec2 coord = go->box.get_center();

  this->associated.box.x = coord.x - go->box.w / 2.0;
  this->associated.box.y = coord.y - go->box.h / 2.0;

  InputManager &input = InputManager::GetInstance();

  int x_value = input.GetMouseX() + Camera::pos.x, y_value = input.GetMouseY() + Camera::pos.y;

  Vec2 first_point = this->associated.box.get_center();

  Vec2 second_point {(float) x_value, (float) y_value};

  this->angle = first_point.inclination_two_points(second_point);

  this->associated.angleDeg = radians_to_degrees(this->angle);

  this->angle = this->associated.angleDeg;

  bool mouse_left_clicked = input.MousePress(LEFT_MOUSE_BUTTON);

  if (mouse_left_clicked && (this->cooldown.Get() >= 1.0f || this->cooldown.initialize)) {
    this->cooldown.Restart();
    this->Shoot();
  }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{
  if (type == "PenguinCannon")
    return true;
  return false;
}

void PenguinCannon::Shoot()
{
  State &state = Game::GetInstance().GetCurrentState();

  Vec2 center = this->associated.box.get_center();

  GameObject *bullet_go = new GameObject();

  bullet_go->box.x = center.x - this->associated.box.w / 2.0;
  bullet_go->box.y = center.y - this->associated.box.h / 2.0;

  string sprite = "assets/img/penguinbullet.png";

  Component *bullet = new Bullet(*bullet_go, this->angle, 5.0F, false, 4, 10, 1000.0F, sprite);

  bullet_go->AddComponent(bullet);

  state.AddObject(bullet_go);
}


void PenguinCannon::NotifyCollision(GameObject &other) {
  Bullet *maybe_bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));

  if (maybe_bullet && maybe_bullet->targetsPlayer) {
    PenguinBody *body = static_cast<PenguinBody *> (this->pbody.lock().get()->GetComponent("PenguinBody"));
    body->hp -= maybe_bullet->GetDamage();
    if (body->hp <= 0) {
      GameObject *death_explosion = new GameObject();

      Sprite *sprite_death = new Sprite(*death_explosion, "assets/img/penguindeath.png", 5, .2F, 1.0F);
      sprite_death->SetScale(.25F, .5F);
      Mixer *explosion_sound = new Mixer(*death_explosion ,"assets/audio/boom.wav");
      explosion_sound->PlaySound();

      death_explosion->AddComponent(sprite_death);
      death_explosion->AddComponent(explosion_sound);
      
      death_explosion->box.x = this->associated.box.x;
      death_explosion->box.y = this->associated.box.y;

      State &game_state = Game::GetInstance().GetCurrentState();

      game_state.AddObject(death_explosion);
    }
  }
}