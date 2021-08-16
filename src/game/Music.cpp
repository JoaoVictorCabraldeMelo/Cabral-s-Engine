#include <iostream>
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