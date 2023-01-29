#include "../include/Timer.hpp"

using namespace std;

Timer::Timer()
    : initialize(true), time(0.0f)
{
}

void Timer::Update(float dt) {
  time += dt;
}

void Timer::Restart() {
  time = 0.0f;
  initialize = false;
}

float Timer::Get() const 
{
  return time;
}