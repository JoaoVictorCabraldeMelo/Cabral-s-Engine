#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <SDL2/SDL_mixer.h>
#include "../include/Music.hpp"
#include "../include/Component.hpp"
#include "../include/Resource.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

using namespace std;

Music::Music(GameObject &associated) : Component(associated)
{
  this->chunk = nullptr;
  this->channel = 0;
}

Music::Music(GameObject &associated, const string &file) : Component(associated)
{
  this->chunk = nullptr;
  this->channel = 0;
  this->Open(file);
}

Music::~Music()
{
  Music::Stop();
}

void Music::Play(int times)
{
  this->channel = Mix_PlayChannel(-1, this->chunk, times);

  /*Deixar sem volume*/
  ControlVolume(-1, 0); 

  if (this->channel == -1)
  {
    ofstream logfile("Erros.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't play the music:" << endl;
    cout << "Error while playing the music: " << Mix_GetError() << endl;
  }
}

void Music::Stop()
{
  if (this->chunk != nullptr)
    Mix_HaltChannel(this->channel);
}

void Music::Open(string file)
{
  Mix_Chunk *music;

  music = Resource::GetSound(file);

  this->chunk = music;
}

bool Music::IsOpen()
{
  if (this->chunk != nullptr)
    return true;
  else
    return false;
}

void Music::Update(float dt)
{
  // cout << dt << endl;
}

bool Music::Is(const string type)
{
  if (type == "Sound")
    return true;
  else
    return false;
}

void Music::Render()
{
}

void Music::ControlVolume(int channel, int volume){
  Mix_Volume(channel, volume);
}