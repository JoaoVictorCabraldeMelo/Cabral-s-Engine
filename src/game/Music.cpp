#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <SDL2/SDL_mixer.h>
#include "../lib/Music.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../lib/SDL_include.h"

Music::Music()
{
  this->music = nullptr;
}

Music::Music(std::string file)
{
  Music::Open(file);
}

Music::~Music()
{
  Music::Stop();

  Mix_FreeMusic(this->music);
}

void Music::Play(int times)
{
  if (this->music != nullptr)
  {
    Mix_PlayMusic(this->music, times);
  }
  else
  {
    std::cout << "There is no music to be played !!" << std::endl;
  }
}

void Music::Stop(int msToStop)
{
  while (!Mix_FadeOutMusic(msToStop) && Mix_PlayingMusic())
  {
    SDL_Delay(100);
  }
}

void Music::Open(std::string file)
{
  Mix_Music *music;

  music = Mix_LoadMUS(file.c_str());

  if (music == nullptr)
  {
    std::ofstream logfile("Errors.log");

    logfile << Mix_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't load the music" << std::endl;
    std::cout << "Error while loading the music: " << Mix_GetError() << std::endl;
  }

  this->music = music;
}

bool Music::IsOpen()
{
  if (this->music != nullptr)
  {
    return true;
  }
  return false;
}
