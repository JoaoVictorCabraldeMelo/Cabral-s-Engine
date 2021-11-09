#include "../include/State.hpp"
#include "../include/Vec2.hpp"
#include "../include/Face.hpp"
#include "../include/Game.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include <iostream>
#include <fstream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#define PI 3.14159265

using namespace std;

State::State()
{
  this->quitRequested = false;

  GameObject *initialize = new GameObject();

  GameObject *tileMapObject = new GameObject();

  TileSet *tileSet = new TileSet(64, 64, "./assets/img/tileset.png");

  Component *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);

  Component *bg = new Sprite(*initialize);

  initialize->AddComponent(bg);

  Component *music = new Music(*initialize);

  initialize->AddComponent(music);

  this->objectArray.emplace_back(initialize);

  this->objectArray.emplace_back(tileMapObject);

  this->LoadAssets();
}

State::~State()
{
  this->objectArray.clear();
}

void State::LoadAssets()
{
  GameObject *initialize = static_cast<GameObject *>(this->objectArray[0].get());

  Sprite *bg = static_cast<Sprite *>(initialize->GetComponent("Image"));

  bg->Open("./assets/img/ocean.jpg");

  bg->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  initialize->box.x = 0;
  initialize->box.y = 0;

  bg->Render();

  Music *music = static_cast<Music *>(initialize->GetComponent("Sound"));

  music->Open("./assets/audio/stageState.ogg");

  music->Play(-1);
}

void State::Update(float dt)
{


  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
  {
    this->quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
  {
    Vec2 objPos = Vec2(200, 0).rotate(-PI + PI * (rand() % 1001) / 500.0) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    AddObject((int)objPos.x, (int)objPos.y);
  }

  for (auto it = this->objectArray.begin(); it < this->objectArray.end(); ++it)
  {
    if ((*it)->IsDead())
      this->RemoveObject(it);
    else
      (*it)->Update(dt);
  }
}

void State::Render()
{

  for (auto &object : objectArray)
    object->Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{

  GameObject *enemy = new GameObject();

  Component *peguin = new Sprite(*enemy, "./assets/img/penguinface.png");

  enemy->AddComponent(peguin);

  Sprite *newEnemy = nullptr;

  newEnemy = static_cast<Sprite *>(peguin);

  enemy->box.x = mouseX;
  enemy->box.y = mouseY;
  enemy->box.w = newEnemy->GetWidth();
  enemy->box.h = newEnemy->GetHeight();

  newEnemy->Render();

  Component *music = new Music(*enemy, "./assets/audio/boom.wav");

  enemy->AddComponent(music);

  Component *face = new Face(*enemy);

  enemy->AddComponent(face);

  this->objectArray.emplace_back(enemy);
}

void State::RemoveObject(vector<unique_ptr<GameObject>>::iterator it)
{
  this->objectArray.erase(it);
}
