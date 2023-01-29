#include "../include/ChapterOne.hpp"
#include "../include/Character.hpp"
#include "../include/GameObject.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

using namespace std;

ChapterOne::ChapterOne() {

  GameObject *bg_go = new GameObject();

  Sprite *background = new Sprite(*bg_go);

  bg_go->AddComponent(background);


  GameObject *character_go = new GameObject();

  Character *bianca = new Character(*character_go, "assets/img/spritesheet.png", 7);

  character_go->AddComponent(bianca);

  AddObject(bg_go);

  AddObject(character_go);
}

ChapterOne::~ChapterOne(){}


void ChapterOne::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());

  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));

  background->Open("assets/img/salafinal.png");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  background->Render();
}

void ChapterOne::Update(float dt) {
  
  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }

  UpdateArray(dt);
}

void ChapterOne::Render() {
  RenderArray();
}

void ChapterOne::Start() {
  LoadAssets();

  StartArray();

  started = true;
}

void ChapterOne::Pause() {}

void ChapterOne::Resume(){
  Camera::Unfollow();
}