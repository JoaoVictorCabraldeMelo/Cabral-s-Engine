#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../lib/Game.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../lib/SDL_include.h"

Game::Game(std::string title, int width, int height)
{
  if (Game::instance != nullptr)
  {
    throw std::runtime_error("More than one game instance running !!");
  }
  Game::instance = this;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    std::ofstream logfile("Errors.log");

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    throw std::runtime_error(SDL_GetError());
  }

  int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

  int initiated_image = IMG_Init(image_flags);

  if ((initiated_image & image_flags) != image_flags)
  {
    std::cout << "Failed to load jpg, png and tif support !!" << std::endl;

    std::cout << "Error Load Image: " << IMG_GetError() << std::endl;
  }
  
  int sound_flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG;

  int initiated_sound = Mix_Init(sound_flags);

  if((initiated_sound & sound_flags) != sound_flags){
    std::cout << "Failed to load mp3, flac, mod and ogg support !!" << std::endl;
    std::cout << "Error Load Sound: " << Mix_GetError() << std::endl;
  }

  
  

}

Game::~Game()
{
}

Game &Game::GetInstance()
{
  if (Game::instance == nullptr)
  {
    Game &game = *new Game("Teste oi", 500, 500);
    return game;
  }
  else
  {
    Game &instance = *Game::instance;
    return instance;
  }
}
