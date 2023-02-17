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

Mixer::Mixer(GameObject &associated) 
: Component(associated), sound(nullptr), music(nullptr), channel(0)
{
}

Mixer::Mixer(GameObject &associated, const string &fileSound) 
: Component(associated), music(nullptr), channel(0)
{
  Mixer::OpenSound(fileSound);
}

Mixer::Mixer(GameObject &associated, const string &fileSound, const string &fileMusic) 
: Component(associated), channel(0)
{
  Mixer::OpenSound(fileSound);
  Mixer::OpenMusic(fileMusic);
}

Mixer::~Mixer()
{
  Mixer::StopSound();
  Mixer::StopMusic();
}

void Mixer::PlaySound(const int times)
{
  channel = Mix_PlayChannel(-1, sound.get(), times);

  if (channel == -1)
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't play the music:" << endl;
    cout << "Error while playing the music: " << Mix_GetError() << endl;

    throw runtime_error(Mix_GetError());
  }
}

void Mixer::PlayMusic(const int times) const {
  int flag = Mix_PlayMusic(music.get(), times);

  if (flag == -1) {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't play the music:" << endl;
    cout << "Error while playing the music: " << Mix_GetError() << endl;

    throw runtime_error(Mix_GetError());
  }
}

void Mixer::StopSound() const
{
  if (sound.get() != nullptr)
    Mix_HaltChannel(channel);
}

void Mixer::StopMusic() const
{
  if (music.get() != nullptr)
    Mix_HaltMusic();
}

void Mixer::StopAllSounds() 
{
  Mix_HaltChannel(-1);
}

/*TODO: Colocar try catch no metodo*/
void Mixer::OpenSound(const string &file)
{
  sound = Resource::GetSound(file);
}

 /*TODO: Colocar try catch no metodo*/
void Mixer::OpenMusic(const string &file){
  music = Resource::GetMusic(file);
}

bool Mixer::IsOpenSound() const
{
  if (sound.get() != nullptr)
    return true;
  return false;
}

bool Mixer::IsOpenMusic() const
{
  if (music.get() != nullptr)
    return true;
  return false;
}

void Mixer::Update(float dt)
{
  // cout << dt << endl;
}

bool Mixer::Is(const string& type)
{
  if (type == "Sound")
    return true;
  else
    return false;
}

void Mixer::Render()
{
}

void Mixer::ControlVolume(int channel, int volume) const 
{
  Mix_Volume(channel, volume);
}