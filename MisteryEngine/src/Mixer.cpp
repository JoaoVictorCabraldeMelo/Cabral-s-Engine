#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <SDL2/SDL_mixer.h>
#include "../include/Mixer.hpp"
#include "../include/Component.hpp"
#include "../include/Resource.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

using namespace std;

Mixer::Mixer(GameObject &associated) : Component(associated)
{
  this->sound = nullptr;
  this->music = nullptr;
  this->channel = 0;
}

Mixer::Mixer(GameObject &associated, const string &fileSound) : Component(associated)
{
  Mixer::OpenSound(fileSound);
  this->music = nullptr;
  this->channel = 0;
}

Mixer::Mixer(GameObject &associated, const string &fileSound, const string &fileMusic) : Component(associated)
{
  Mixer::OpenSound(fileSound);
  Mixer::OpenMusic(fileMusic);
  this->channel = 0;
}

Mixer::~Mixer()
{
  Mixer::StopSound();
  Mixer::StopMusic();
}

void Mixer::PlaySound(int times)
{
  this->channel = Mix_PlayChannel(-1, this->sound.get(), times);

  if (this->channel == -1)
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't play the music:" << endl;
    cout << "Error while playing the music: " << Mix_GetError() << endl;

    throw runtime_error(Mix_GetError());
  }
}

void Mixer::PlayMusic(int times) {
  int flag = Mix_PlayMusic(this->music.get(), times);

  if (flag == -1) {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't play the music:" << endl;
    cout << "Error while playing the music: " << Mix_GetError() << endl;

    throw runtime_error(Mix_GetError());
  }
}

void Mixer::StopSound()
{
  if (this->sound.get() != nullptr)
    Mix_HaltChannel(this->channel);
}

void Mixer::StopMusic()
{
  if (this->music.get() != nullptr)
    Mix_HaltMusic();
}

void Mixer::OpenSound(const string &file)
{
  this->sound = Resource::GetSound(file);
}

void Mixer::OpenMusic(const string &file){
  this->music = Resource::GetMusic(file);
}

bool Mixer::IsOpenSound()
{
  if (this->sound.get() != nullptr)
    return true;
  return false;
}

bool Mixer::IsOpenMusic()
{
  if (this->music.get() != nullptr)
    return true;
  return false;
}

void Mixer::Update(float dt)
{
  // cout << dt << endl;
}

bool Mixer::Is(const string type)
{
  if (type == "Sound")
    return true;
  else
    return false;
}

void Mixer::Render()
{
}

void Mixer::ControlVolume(int channel, int volume){
  Mix_Volume(channel, volume);
}