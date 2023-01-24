#include "../include/TitleState.hpp"
#include "../include/GameObject.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/StageState.hpp"
#include "../include/Camera.hpp"

using namespace std;

TitleState::TitleState() {
  GameObject *title_go = new GameObject();

  Sprite *background_title = new Sprite(*title_go);

  title_go->AddComponent(background_title);

  this->objectArray.emplace_back(title_go);
}

TitleState::~TitleState(){};

void TitleState::LoadAssets() {

  GameObject *title_go = static_cast<GameObject*>(this->objectArray[0].get());

  Sprite *background = static_cast<Sprite*> (title_go->GetComponent("Image"));

  background->Open("assets/img/title.jpg");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  title_go->box.x = 0;
  title_go->box.y = 0;

  background->Render();
}

void TitleState::Update(float dt) {

  Camera::Update(dt);

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
    this->quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    StageState *new_stage = new StageState();
    Game::GetInstance().Push(new_stage);
  }

  this->UpdateArray(dt);
}

void TitleState::Render() {
  this->RenderArray();
}

void TitleState::Start() {
  this->StartArray();

  this->LoadAssets();

  this->started = true;
}

void TitleState::Pause(){}

void TitleState::Resume(){
  Camera::Unfollow();
};