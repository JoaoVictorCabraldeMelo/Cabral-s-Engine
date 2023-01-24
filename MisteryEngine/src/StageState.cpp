#include "../include/StageState.hpp"
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

StageState::StageState()
{

  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");

  this->tileSet = tileSet;

  GameObject *tileMapObject = new GameObject();

  Component *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);



  GameObject *initialize = new GameObject();

  Component *bg = new Sprite(*initialize);

  Component *cameraFollower = new CameraFollower(*initialize);

  this->backgroundMusic = new Music(*initialize);

  initialize->AddComponent(bg);

  initialize->AddComponent(cameraFollower);

  initialize->AddComponent(backgroundMusic);



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
}

void StageState::Start() {

  this->LoadAssets();

  this->StartArray();

  this->started = true;
}

void StageState::Pause(){};

void StageState::Resume(){};

void StageState::LoadAssets()
{
  GameObject *initialize = static_cast<GameObject *>(this->objectArray[0].get());

  Sprite *bg = static_cast<Sprite *>(initialize->GetComponent("Image"));

  bg->Open("./assets/img/ocean.jpg");

  bg->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  initialize->box.x = 0;
  initialize->box.y = 0;

  bg->Render();

  this->backgroundMusic->Open("./assets/audio/stageState.ogg");

  this->backgroundMusic->Play(-1);
}

void StageState::Update(float dt)
{

  Camera::Update(dt);

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().QuitRequested())
    this->quitRequested = true;
  
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    this->popRequested = true;

  this->UpdateArray(dt);

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

    Collider *first_collider = static_cast<Collider *> (first_box->GetComponent("Collider"));
    Collider *second_collider = static_cast<Collider *> (second_box->GetComponent("Collider"));

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

void StageState::Render()
{
  this->RenderArray();
}
