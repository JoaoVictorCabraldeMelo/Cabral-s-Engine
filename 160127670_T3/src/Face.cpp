#include "../include/Face.hpp"
#include "../include/Music.hpp"

#include <chrono>
#include <thread>

using namespace std;

Face::Face(GameObject &associated) : Component(associated)
{
  this->hitpoints = 30;
}

Face::~Face()
{
}

void Face::Damage(int damage)
{
  if (this->hitpoints <= 0)
  {

    Music *Sound = static_cast<Music *>(this->associated.GetComponent("Sound"));

    if (Sound != nullptr)
    {
      Sound->Play();
    }
    
    this_thread::sleep_for(chrono::nanoseconds(10));

    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));

    this->associated.RequestDelete();
  }
  else
  {
    this->hitpoints -= damage;
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