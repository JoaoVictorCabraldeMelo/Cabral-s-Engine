#include "../include/ChapterOne.hpp"
#include "../include/Character.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

using namespace std;

ChapterOne::ChapterOne() : inventory(new GameObject()) {

  GameObject *bg_go = new GameObject();

  Sprite *background = new Sprite(*bg_go);

  bg_go->AddComponent(background);


  GameObject *character_go = new GameObject();

  Character *bianca = new Character(*character_go, "assets/img/spritesheet.png", 7);

  character_go->AddComponent(bianca);

  
  GameObject *inventory_icon_go = new GameObject();

  Sprite *inventory_sprite = new Sprite(*inventory_icon_go, "assets/img/bookIcon.png");

  inventory_icon_go->AddComponent(inventory_sprite);


  AddObject(bg_go);

  AddObject(character_go);

  AddObject(inventory_icon_go);

  AddObject(inventory);
}

ChapterOne::~ChapterOne(){}


void ChapterOne::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());

  GameObject *inventory_go = static_cast<GameObject *>(objectArray[2].get());

  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));

  background->Open("assets/img/salafinal.png");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  inventory_go->box.x = 30 * Game::GetInstance().GetScreenScale().x;
  inventory_go->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  inventory->box.x = 300 * Game::GetInstance().GetScreenScale().x;
  inventory->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  background->Render();
}

void ChapterOne::Update(float dt) {

  InputManager &input = InputManager::GetInstance();

  Component *inventory_cpt = inventory->GetComponent("Image");

  input.Update();

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }
  else if (input.KeyPress(TAB_KEY) && inventory_cpt == nullptr)
  {
    Sprite *inventory_menu_sprite = new Sprite(*inventory, "assets/img/inventory.png");
    inventory->AddComponent(inventory_menu_sprite);
  }
  else if (input.KeyPress(TAB_KEY) &&  inventory_cpt != nullptr)
  {
    inventory->RemoveComponent(inventory_cpt);
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