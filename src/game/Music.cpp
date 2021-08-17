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

int main(int agrc, char **argv)
{

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    std::ofstream logfile("Errors.log");

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    throw std::runtime_error(SDL_GetError());
  }


  int sound_flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG;

  int initiated_sound = Mix_Init(sound_flags);

  if ((initiated_sound & sound_flags) != sound_flags)
  {
    std::cout << "Failed to load mp3, flac, mod and ogg support !!" << std::endl;
    std::cout << "Error Load Sound: " << Mix_GetError() << std::endl;
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
  {
    std::cout << "Couldn't open Audio format configuration !!" << std::endl;
  }

  Mix_AllocateChannels(32);

  Music *music = new Music();

  music->Open("teste.mp3");

  music->Play(-1);

  std::chrono::milliseconds timespan(30000);

  std::this_thread::sleep_for(timespan);

  music->Stop();

  Mix_CloseAudio();

  Mix_Quit();

  SDL_Quit();

  return 0;
}