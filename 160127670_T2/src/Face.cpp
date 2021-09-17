#include "../include/Face.hpp"
#include "../include/Music.hpp"

using namespace std;

Face::Face() : Component()
{
  this->hitpoints = 30;
}

Face::~Face() {
}

void Face::Damage(int damage)
{
  this->hitpoints -= damage;
  if (this->hitpoints <= 0)
  {
    this->associated.RequestDelete();

    Music *Sound = static_cast<Music *> (this->associated.GetComponent("Sound"));

    if (Sound != nullptr)
    {
      Sound->Play();
    }
  }
}

void Face::Update(float dt)
{
  // cout << dt << endl;
}

void Face::Render()
{
}

bool Face::Is(const string type)
{
  if (type == "Face")
    return true;
  else
    return false;
}