#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../include/Game.hpp"
#include "../include/Resource.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height)
{

  /*Default Initialization*/
  srand(time(NULL));

  if (Game::instance != nullptr)
  {
    throw std::runtime_error("More than one game instance running !!");
  }

  this->instance = this;

  this->title = title;
  this->width = width;
  this->height = height;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    throw std::runtime_error(SDL_GetError());
  }



  /*Image Initialization*/
  int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

  int initiated_image = IMG_Init(image_flags);

  if ((initiated_image & image_flags) != image_flags)
  {
    std::cout << "Failed to load jpg, png and tif support !!" << std::endl;

    std::cout << "Error Load Image: " << IMG_GetError() << std::endl;
  }



   /*Sound Initialization*/
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


  /*Font Initialization*/
  int font_flag = TTF_Init();

  if (font_flag != 0) {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << TTF_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't initialize TTF!!" << std::endl;
    std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;

    throw std::runtime_error(TTF_GetError());
  }


  /*Window Initialization*/
  this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (this->window == nullptr)
  {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't create Window!!" << std::endl;
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }



  /*Renderer Initialization*/
  int renderer_flags = SDL_RENDERER_ACCELERATED;

  this->renderer = SDL_CreateRenderer(this->window, -1, renderer_flags);

  if (this->renderer == nullptr)
  {
    std::ofstream logfile("Errors.log", std::ofstream::app);

    logfile << SDL_GetError() << std::endl;

    logfile.close();

    std::cout << "Couldn't create Renderer for Window !!" << std::endl;
    std::cout << "Error creating Renderer: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }


  /*State Initialization*/
  this->storedState = nullptr;
}

Game::~Game()
{

  if (this->storedState != nullptr) {
    this->storedState = nullptr;
    while(!this->stateStack.empty()){
      this->stateStack.top().get()->~State();
      this->stateStack.pop();
    }
  }

  SDL_DestroyRenderer(this->renderer);

  SDL_DestroyWindow(this->window);

  Mix_CloseAudio();

  Mix_Quit();

  IMG_Quit();

  TTF_Quit();

  SDL_Quit();
}

Game &Game::GetInstance()
{
  if (Game::instance == nullptr)
  {
    Game &game = *new Game("160127670", 1024, 600);
    return game;
  }
  else
  {
    Game &instance = *Game::instance;
    return instance;
  }
}

SDL_Renderer *Game::GetRenderer()
{
  return this->renderer;
}

State &Game::GetCurrentState() { return *this->stateStack.top().get(); }

void Game::Push(State *state) {
  this->storedState = state;
}

int Game::GetHeight()
{
  return this->height;
}

int Game::GetWidth()
{
  return this->width;
}

void Game::Run()
{

  if (this->storedState != nullptr) {
    this->stateStack.emplace(storedState);
    this->storedState = nullptr;
    this->GetCurrentState().Start();

    //Game Loop
    while (!this->stateStack.empty() &&  !this->GetCurrentState().QuitRequested())
    {
      if (this->GetCurrentState().PopRequested()){
        this->stateStack.pop();
        if (!this->stateStack.empty())
          this->GetCurrentState().Resume();
      }

      if (this->storedState != nullptr){
        this->GetCurrentState().Pause();
        this->stateStack.emplace(storedState);
        this->GetCurrentState().Start();
        this->storedState = nullptr;
      }

      this->CalculateDeltaTime();
      this->GetCurrentState().Update(this->GetDeltaTime());
      this->GetCurrentState().Render();

      SDL_RenderPresent(this->renderer);

      SDL_Delay(33);
    }

    //Clear State Stack
    while(!this->stateStack.empty()) {
      this->stateStack.pop();
    }
  }

  Resource::ClearImages();
  Resource::ClearMusic();
  Resource::ClearSounds();
  Resource::ClearFont();
}

void Game::CalculateDeltaTime()
{
  int currentTime = (int) SDL_GetTicks();

  this->dt = (currentTime - frameStart) / 1000.0;

  this->frameStart = currentTime;
}

float Game::GetDeltaTime()
{
  return this->dt;
}