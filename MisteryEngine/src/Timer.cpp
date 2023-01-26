#include "../include/Timer.hpp"

using namespace std;

Timer::Timer() {
  this->time = 0.0f;
  this->initialize = true;
}

void Timer::Update(float dt) {
  this->time += dt;
}

void Timer::Restart() {
  this->time = 0.0f;
  this->initialize = false;
}

float Timer::Get() {
  return this->time;
}