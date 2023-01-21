#include "../include/State.hpp"
#include "../include/Vec2.hpp"
#include "../include/Game.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"
#include "../include/Alien.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/Collision.hpp"
#include "../include/Collider.hpp"

#include <iostream>
#include <fstream>
#include <set>

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

  this->started = false;

  GameObject *initialize = new GameObject();

  GameObject *tileMapObject = new GameObject();

  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");

  Component *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);

  Component *bg = new Sprite(*initialize);

  initialize->AddComponent(bg);

  Component *cameraFollower = new CameraFollower(*initialize);

  initialize->AddComponent(cameraFollower);

  Component *music = new Music(*initialize);

  initialize->AddComponent(music);

  this->objectArray.emplace_back(initialize);

  this->objectArray.emplace_back(tileMapObject);

  GameObject *alienObject = new GameObject();

  Component *alien = new Alien(*alienObject, 7);

  alienObject->AddComponent(alien);

  this->objectArray.emplace_back(alienObject);

  GameObject *penguinObject = new GameObject();

  Component *penguin = new PenguinBody(*penguinObject);

  penguinObject->AddComponent(penguin);

  this->objectArray.emplace_back(penguinObject);

  penguinObject->box.x = 704;
  penguinObject->box.y = 640;

  Camera::Follow(penguinObject);

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

  Camera::Update(dt);

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
  {
    this->quitRequested = true;
  }

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    this->objectArray[i]->Update(dt);
  }

  set<pair<GameObject*, GameObject*>> collisions;

  for (int i = 0; i < (int)this->objectArray.size(); i++){
    for (int j = i; j < (int)this->objectArray.size();j++){
      if (i != j) {
        GameObject *go_i = this->objectArray[i].get();
        GameObject *go_j = this->objectArray[j].get();
        if (go_i->GetComponent("Collider") && go_j->GetComponent("Collider"))
          collisions.insert(make_pair(go_i, go_j));
      }
    }
  }

  for (auto &collision : collisions) {
    GameObject *first_box = collision.first;
    GameObject *second_box = collision.second;

    Collider *first_collider = (Collider *) first_box->GetComponent("Collider");
    Collider *second_collider = (Collider *)second_box->GetComponent("Collider");

    bool collided = Collision::IsColliding(first_collider->box, second_collider->box, first_box->angleDeg, second_box->angleDeg);

    if (collided) {
      first_box->NotifyCollision(*second_box);
      second_box->NotifyCollision(*first_box);
    }
  }

    for (int i = 0; i < (int)this->objectArray.size(); i++)
    {
      if (this->objectArray[i]->IsDead())
      {
        this->RemoveObject(i);
        i--;
      }
    }
}

void State::Render()
{
  for (int i = 0; i < (int)this->objectArray.size(); i++)
    this->objectArray[i]->Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{

  shared_ptr<GameObject> shared_go(go);

  this->objectArray.push_back(shared_go);

  if (this->started)
    shared_go->Start();

  weak_ptr<GameObject> weak_go(shared_go);

  return weak_go;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    if (this->objectArray[i].get() == go)
    {
      weak_ptr<GameObject> weak_go(this->objectArray[i]);
      return weak_go;
    }
  }

  return {};
}

void State::RemoveObject(int position)
{
  this->objectArray.erase(this->objectArray.begin() + position);
}

void State::Start()
{

  this->LoadAssets();

  for (int i = 0; i < (int)this->objectArray.size(); i++)
    this->objectArray[i]->Start();

  this->started = true;
}
