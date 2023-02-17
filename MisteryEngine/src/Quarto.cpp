#include "../include/Quarto.hpp"
#include "../include/Sprite.hpp"
#include "../include/Character.hpp"
#include "../include/Mouse.hpp"
#include "../include/Loading.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Dialog.hpp"
#include "../include/Armario.hpp"

using namespace std;

Quarto::Quarto()
    : inventory(new GameObject()), inventory_icon(new GameObject()), bianca(new GameObject()),
      background(new GameObject()), mouse(new GameObject()), loading_screen(new GameObject()), dialog_screen(new GameObject()), 
      dialogs(new GameObject()), timer(Timer()), wardrobe(new GameObject()), bed(new GameObject()), door(new GameObject())
{
  Sprite *background_sprite = new Sprite(*background);

  background->AddComponent(background_sprite);

  Character *bianca_character = new Character(*bianca, "assets/img/bianca.png", 6);

  bianca->AddComponent(bianca_character);

  Sprite *inventory_sprite = new Sprite(*inventory_icon, "assets/img/bookIcon.png");

  inventory_icon->AddComponent(inventory_sprite);

  Mouse *mouse_cpt = new Mouse(*mouse, "assets/img/cursor.png");

  mouse->AddComponent(mouse_cpt);

  vector<string> actions_wardrobe = {};

  actions_wardrobe.push_back("Procurar");
  actions_wardrobe.push_back("Voltar");

  Armario *wardrobe_obj = new Armario(*wardrobe, "assets/img/wardrobe.png", actions_wardrobe, *mouse, {1.0f, 1.0f});

  wardrobe->AddComponent(wardrobe_obj);



  vector<string> loading = {};

  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.2.png");
  loading.push_back("assets/img/loading1.3.png");
  loading.push_back("assets/img/loading1.4.png");
  loading.push_back("assets/img/loading1.5.png");
  loading.push_back("assets/img/loading1.6.png");
  loading.push_back("assets/img/loading1.7.png");
  loading.push_back("assets/img/loading1.8.png");
  loading.push_back("assets/img/loading1.9.png");
  loading.push_back("assets/img/loading1.10.png");

  Loading *loading_obj = new Loading(*loading_screen, loading);

  loading_screen->AddComponent(loading_obj);




  GameObject *music_go = new GameObject();

  Mixer *music = new Mixer(*music_go);

  music->OpenMusic("assets/audio/happy_theme.mp3");

  music->OpenSound("assets/audio/fade_sound.mp3");

  this->music = music;

  music->PlaySound(0);

  AddObject(background);

  AddObject(wardrobe);

  AddObject(bianca);

  AddObject(inventory_icon);

  AddObject(inventory);

  AddObject(mouse);

  AddObject(loading_screen);

  AddObject(music_go);

}

Quarto::~Quarto() {

}


void Quarto::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());

  GameObject *inventory_go = static_cast<GameObject *>(objectArray[2].get());


  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));

  background->Open("assets/img/Quarto.png");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  wardrobe->box.x = 3 * Game::GetInstance().GetScreenScale().x;
  wardrobe->box.y = 350 * Game::GetInstance().GetScreenScale().y;

  inventory_go->box.x = 30 * Game::GetInstance().GetScreenScale().x;
  inventory_go->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  inventory->box.x = 300 * Game::GetInstance().GetScreenScale().x;
  inventory->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  background->Render();
}


void Quarto::Update(float dt) {

  timer.Update(dt);

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
  else if (input.KeyPress(TAB_KEY) && inventory_cpt != nullptr)
  {
    inventory->RemoveComponent(inventory_cpt);
  }

  if (timer.Get() > 2.0F)
  {
    if (first_time == 0)
    {
      vector<string> dialog = {};

      dialog.push_back("assets/img/dial1.png");
      dialog.push_back("assets/img/dial2.png");
      dialog.push_back("assets/img/dial3.png");
      dialog.push_back("assets/img/dial4.png");
      dialog.push_back("assets/img/dial5.png");
      dialog.push_back("assets/img/dial6.png");
      dialog.push_back("assets/img/dial7.png");

      Loading *dialog_obj = new Loading(*dialog_screen, dialog, 2.0F);

      dialog_screen->AddComponent(dialog_obj);

      AddObject(dialog_screen);

      music->PlayMusic(-1);
      first_time = 1;
    }
  }

  if (timer.Get() > 17.0f && !flag_initial_dialogs)
  {
    flag_initial_dialogs = true;
    vector<string> dialogs_ar = {};

    dialogs_ar.push_back("assets/img/01.png");
    dialogs_ar.push_back("assets/img/02.png");
    dialogs_ar.push_back("assets/img/03.png");

    Dialog *dialogs_obj = new Dialog(*dialogs, dialogs_ar, 2.0f);

    dialogs->AddComponent(dialogs_obj);

    AddObject(dialogs);
  }

  UpdateArray(dt);
}

void Quarto::Render() {
  RenderArray();
}

void Quarto::Start() {
  LoadAssets();

  StartArray();

  started = true;

  GameObject *bianca_go = static_cast<GameObject *>(objectArray[2].get());

  bianca_go->box.x = 700 * Game::GetInstance().GetScreenScale().x;
  bianca_go->box.y = 400 * Game::GetInstance().GetScreenScale().y;
}

void Quarto::Pause () {}

void Quarto::Resume(){
  Camera::Unfollow();
}